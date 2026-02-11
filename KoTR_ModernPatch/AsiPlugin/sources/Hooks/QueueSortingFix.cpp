#include "QueueSortingFix.h"

#include "../Utils/ModUtils/Facade.hpp"
#include "../Utils/ModUtils/HookEach.hpp"
#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h"

#include "../GameApp/IntrusiveQueue.h"

struct TerrainGreedNode;

class TerrainData;
class TerrainDataFacade
{
public:
	TerrainDataFacade(TerrainData* obj)
		: FACADE_INIT_MEMBER(obj, m_queue)
	{}

public:
	using QueueType = IntrusiveQueue<TerrainGreedNode>;
	FACADE_MEMBER(QueueType*, m_queue);
};

struct MarineGreedNode;

class MarineData;
class MarineDataFacade
{
public:
	MarineDataFacade(MarineData* obj)
		: FACADE_INIT_MEMBER(obj, m_queue)
	{}

public:
	using QueueType = IntrusiveQueue<MarineGreedNode>;
	FACADE_MEMBER(QueueType*, m_queue);
};

// Reused by both variations of the queue that we're patching
static void (__thiscall* orgGreedNodeMerge)(void* queue);

template<std::size_t Index>
static void (__thiscall* orgTerrainDataSort)(TerrainData* obj);
template<std::size_t Index>
static void __fastcall TerrainDataSort_PreMerge(TerrainData* obj)
{
	orgGreedNodeMerge(TerrainDataFacade(obj).m_queue);
	orgTerrainDataSort<Index>(obj);
}

template<std::size_t Index>
static void (__thiscall* orgMarineDataSort)(MarineData* obj);
template<std::size_t Index>
static void __fastcall MarineDataSort_PreMerge(MarineData* obj)
{
	orgGreedNodeMerge(MarineDataFacade(obj).m_queue);
	orgMarineDataSort<Index>(obj);
}

HOOK_EACH_INIT(TerrainDataSort, orgTerrainDataSort, TerrainDataSort_PreMerge);
HOOK_EACH_INIT(MarineDataSort, orgMarineDataSort, MarineDataSort_PreMerge);

bool QueueSortingFix::injectHooks() try
{
	using namespace Memory::VP;
	using namespace hook::txn;

	// The remaining patches are context-specific and can partially fail, but this one is an absolute prerequisite for them all.
	auto dec_rebalance_counter = pattern("40 89 46 08 5E C2").count(4);
	dec_rebalance_counter.for_each_result([](pattern_match match) {
		Patch<uint8_t>(match.get<void>(), 0x48); // dec eax	
	});

	orgGreedNodeMerge = reinterpret_cast<decltype(orgGreedNodeMerge)>(get_pattern_uintptr("53 55 33 ED 56 3B C5 57 89 4C 24", -6));

	bool bAnyPatchesApplied = false;

	// Greystone heightmaps
	try
	{
		std::array<void*, 3> terrain_data_sort = {
			get_pattern("E8 ? ? ? ? 8B 44 24 ? 8B 0B"),
			get_pattern("E8 ? ? ? ? 8B 0B E8"),
			get_pattern("E8 ? ? ? ? 8B 54 24 ? 52 E8 ? ? ? ? 8B 44 24 ? 50"),
		};

		auto terrain_data_sort_patch_src = pattern("8B 4E ? 8B 46 ? 8B 11 85 D2").get_one();
		auto terrain_data_sort_patch_dest = get_pattern("8B 54 24 ? 52 50 E8 ? ? ? ? 89 7E");

		FACADE_SET_MEMBER_OFFSET(TerrainDataFacade, m_queue, *terrain_data_sort_patch_src.get<uint8_t>(2));

		HookEach_TerrainDataSort(terrain_data_sort, InterceptCall);

		// Patch the merge function to always only consider m_list->m_persistent
		// mov edi, [ecx]
		// jmp loc_60C805
		Patch(terrain_data_sort_patch_src.get<void>(6), { 0x8B, 0x39 });
		InjectHook(terrain_data_sort_patch_src.get<void>(8), terrain_data_sort_patch_dest, HookType::Jump);

		bAnyPatchesApplied = true;
	}
	TXN_CATCH();

	// "Marine data"
	try
	{
		std::array<void*, 2> marine_data_sort = {
			get_pattern("E8 ? ? ? ? 8B 0F E8"),
			get_pattern("E8 ? ? ? ? 8B 4C 24 ? 51 E8 ? ? ? ? 8B 54 24 ? 52"),
		};

		// No shorter pattern is feasible...
		auto marine_data_sort_patch_src = pattern("8B 4E ? 8B 56 ? D9 5C 24 ? 8B 01 85 C0 74 ? 85 D2 74 ? 8D 7A ? EB ? 33 FF 3B 78 ? 75 ? 8B 79 ? EB ? 8B 79 ? 85 FF 74 ? 85 D2 74 ? 8D 42 ? EB ? 33 C0 3B 47 ? 74 ? 8B 42 ? 85 C0 74 ? 8D 78 ? EB ? 33 FF 8B 44 24 ? 50 52 E8 ? ? ? ? 89 7E")
											.get_one();
		auto marine_data_sort_patch_dest = get_pattern("8B 44 24 ? 50 52 E8 ? ? ? ? 89 7E");
		
		FACADE_SET_MEMBER_OFFSET(MarineDataFacade, m_queue, *marine_data_sort_patch_src.get<uint8_t>(2));

		HookEach_MarineDataSort(marine_data_sort, InterceptCall);

		// Patch the merge function to always only consider m_list->m_persistent
		// mov edi, [ecx]
		// jmp loc_60C805
		Patch(marine_data_sort_patch_src.get<void>(10), { 0x8B, 0x39 });
		InjectHook(marine_data_sort_patch_src.get<void>(12), marine_data_sort_patch_dest, HookType::Jump);

		bAnyPatchesApplied = true;
	}
	TXN_CATCH();

	return bAnyPatchesApplied;
}
catch (const hook::txn_exception&)
{
	return false;
}
