Public Class Form_Main

    Private Sub Btn_Save_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub Btn_Exit_Click(sender As Object, e As EventArgs) Handles Btn_Exit.Click
        Application.Exit()
        End
    End Sub

    Private Sub Btn_RunGame_Click(sender As Object, e As EventArgs) Handles Btn_RunGame.Click
        Process.Start(".\king.exe", Application.ExecutablePath)
    End Sub

    Private Sub vk_link_Click(sender As Object, e As EventArgs) Handles vk_link.Click
        Process.Start("http://vk.com/rnr_mods")
    End Sub

    Private Sub Form_Main_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Dim lang As String = Space$(16)
        'langv=rus eng spa fra ger
        GetPrivateProfileStringA("ENV", "langv", "eng", lang, 16, ".\\truck.ini")

        'if not Russian language in truck.ini
        If Not lang.Contains("rus") Then
            SetEngLocalization()
        End If

        LoadParameters()

        'fix paths in truck.ini for ModuleLoader
        'home=.\
        'base=.\
        'movie=.\
        'source=.\
        WritePrivateProfileStringA("INSTALL", "home", ".\", ".\\truck.ini")
        WritePrivateProfileStringA("INSTALL", "base", ".\", ".\\truck.ini")
    End Sub

    'patches switches
    Private Sub CBox_CollisionMod_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_CollisionMod.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_CollisionMod.Checked), ".\\plugins\KoTR_CollisionMod.ini")
    End Sub

    Private Sub CBox_PhysicsMod_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_PhysicsMod.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_PhysicsMod.Checked), ".\\plugins\KoTR_PhysicsMod.ini")
    End Sub

    Private Sub CBox_CameraMod_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_CameraMod.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_CameraMod.Checked), ".\\plugins\KoTR_CameraMod.ini")
    End Sub

    Private Sub CBox_DustPatch_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_DustPatch.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_DustPatch.Checked), ".\\plugins\KoTR_DustPatch.ini")
    End Sub

    Private Sub CBox_MirrorsFix_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_MirrorsFix.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_MirrorsFix.Checked), ".\\plugins\KoTR_MirrorsFix.ini")
    End Sub

    'mods switches
    Private Sub CBox_VehicleMod_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_VehicleMod.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_VehicleMod.Checked), ".\\plugins\KoTR_VehicleMod.ini")
    End Sub

    Private Sub CBox_InteriorMod_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_InteriorMod.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_InteriorMod.Checked), ".\\plugins\KoTR_InteriorMod.ini")
    End Sub

    Private Sub CBox_UpgradesMod_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_UpgradesMod.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_UpgradesMod.Checked), ".\\plugins\KoTR_UpgradesMod.ini")
    End Sub

    Private Sub CBox_TabloMod_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_TabloMod.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_TabloMod.Checked), ".\\plugins\KoTR_TabloMod.ini")
    End Sub

    Private Sub CBox_RainMod_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_RainMod.CheckedChanged
        WritePrivateProfileIntA("MOD", "Enabled", Int(CBox_RainMod.Checked), ".\\plugins\KoTR_RainMod.ini")
    End Sub

    'settings switches
    Private Sub TBox_ModifierKey_KeyPress(sender As Object, e As KeyEventArgs) Handles TBox_ModifierKey.KeyUp
        TBox_ModifierKey.Text = [Enum].GetName(GetType(Keys), e.KeyValue)
        WritePrivateProfileIntA("KEYBINDINGS", "ModifierKey", e.KeyValue, ".\\plugins\KoTR_CameraMod.ini")
    End Sub

    Private Sub TBox_TurnSignalRKey_KeyPress(sender As Object, e As KeyEventArgs) Handles TBox_TurnSignalRKey.KeyUp
        TBox_TurnSignalRKey.Text = [Enum].GetName(GetType(Keys), e.KeyValue)
        WritePrivateProfileIntA("KEYBINDINGS", "TurnSignalRKey", e.KeyValue, ".\\plugins\KoTR_VehicleMod.ini")
    End Sub

    Private Sub TBox_TurnSignalLKey_KeyPress(sender As Object, e As KeyEventArgs) Handles TBox_TurnSignalLKey.KeyUp
        TBox_TurnSignalLKey.Text = [Enum].GetName(GetType(Keys), e.KeyValue)
        WritePrivateProfileIntA("KEYBINDINGS", "TurnSignalLKey", e.KeyValue, ".\\plugins\KoTR_VehicleMod.ini")
    End Sub

    Private Sub TBox_TurnSignalHKey_KeyPress(sender As Object, e As KeyEventArgs) Handles TBox_TurnSignalHKey.KeyUp
        TBox_TurnSignalHKey.Text = [Enum].GetName(GetType(Keys), e.KeyValue)
        WritePrivateProfileIntA("KEYBINDINGS", "TurnSignalHKey", e.KeyValue, ".\\plugins\KoTR_VehicleMod.ini")
    End Sub

    Private Sub CBox_D2GIScrFormat_SelectedIndexChanged(sender As Object, e As EventArgs) Handles CBox_D2GIScrFormat.SelectedIndexChanged
        WritePrivateProfileStringA("SCREENSHOTS", "image_format", CBox_D2GIScrFormat.Text, ".\\d2gi.ini")
    End Sub

    Private Sub CBox_VSync_CheckedChanged(sender As Object, e As EventArgs) Handles CBox_VSync.CheckedChanged
        WritePrivateProfileIntA("VIDEO", "EnableVSync", Int(CBox_VSync.Checked), ".\\d2gi.ini")
    End Sub
    ' ************************************************************************************************************************************** '

    Private Sub LoadParameters()
        Dim tempInt As Integer

        'patches tab
        CBox_CollisionMod.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_CollisionMod.ini")
        CBox_PhysicsMod.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_PhysicsMod.ini")
        CBox_CameraMod.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_CameraMod.ini")
        CBox_DustPatch.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_DustPatch.ini")
        CBox_MirrorsFix.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_MirrorsFix.ini")

        'mods tab
        CBox_VehicleMod.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_VehicleMod.ini")
        CBox_InteriorMod.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_InteriorMod.ini")
        CBox_UpgradesMod.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_UpgradesMod.ini")
        CBox_TabloMod.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_TabloMod.ini")
        CBox_RainMod.Checked = GetPrivateProfileIntA("MOD", "Enabled", 0, ".\\plugins\KoTR_RainMod.ini")

        'settings tab
        tempInt = GetPrivateProfileIntA("KEYBINDINGS", "ModifierKey", 32, ".\\plugins\KoTR_CameraMod.ini")
        TBox_ModifierKey.Text = [Enum].GetName(GetType(Keys), tempInt)

        tempInt = GetPrivateProfileIntA("KEYBINDINGS", "TurnSignalRKey", 32, ".\\plugins\KoTR_VehicleMod.ini")
        TBox_TurnSignalRKey.Text = [Enum].GetName(GetType(Keys), tempInt)

        tempInt = GetPrivateProfileIntA("KEYBINDINGS", "TurnSignalLKey", 32, ".\\plugins\KoTR_VehicleMod.ini")
        TBox_TurnSignalLKey.Text = [Enum].GetName(GetType(Keys), tempInt)

        tempInt = GetPrivateProfileIntA("KEYBINDINGS", "TurnSignalHKey", 32, ".\\plugins\KoTR_VehicleMod.ini")
        TBox_TurnSignalHKey.Text = [Enum].GetName(GetType(Keys), tempInt)

        Dim screenshotsFormat As String = Space$(4)
        GetPrivateProfileStringA("SCREENSHOTS", "image_format", "jpg", screenshotsFormat, 4, ".\\d2gi.ini")

        'jpg bmp png
        If screenshotsFormat.Contains("jpg") Then
            CBox_D2GIScrFormat.SelectedIndex = 0
        ElseIf screenshotsFormat.Contains("png") Then
            CBox_D2GIScrFormat.SelectedIndex = 1
        ElseIf screenshotsFormat.Contains("bmp") Then
            CBox_D2GIScrFormat.SelectedIndex = 2
        Else
            CBox_D2GIScrFormat.SelectedIndex = 0
        End If

        CBox_VSync.Checked = GetPrivateProfileIntA("VIDEO", "EnableVSync", 0, ".\\d2gi.ini")
    End Sub

    Private Sub SetEngLocalization()
        'header
        Me.Text = "Launcher"

        'down buttons
        'Btn_Save.Text = "Save settings"
        Btn_RunGame.Text = "Start the game"
        Btn_Exit.Text = "Exit"
        lbl_Version.Text = "Version 1.00 (2025.11.04). Updates and news are available here:"
        vk_link.Location = New Point(315, 414)

        'tabs labels
        TControl_UI.TabPages(0).Text = "Patches"
        TControl_UI.TabPages(1).Text = "Mods"
        TControl_UI.TabPages(2).Text = "Settings"
        TControl_UI.TabPages(3).Text = "About"

        'page_patches
        CBox_CollisionMod.Text = "Reconfigured collision handling"
        Dsr_CollisionMod.Text = "Partially corrects the ""sticking"" of vehicles in collisions. If active, the ability to knock down" & vbNewLine & "trees in the game is disable."

        CBox_PhysicsMod.Text = "Reconfigured parameters of road trains movement"
        Dsr_PhysicsMod.Text = "Experimental modification. Reduces the inertia of road trains in simulator mode. In the arcade" & vbNewLine & "mode, it slightly reduces the skidding of semi-trailers. At low frame rate, it has the opposite" & vbNewLine & "effect."

        CBox_CameraMod.Text = "Fixed external camera position when third-person view mode enabled"
        Dsr_CameraMod.Text = "Corrects the ""flying away"" external camera behaviour. The camera moves faster if the" & vbNewLine & "modifier key is held down together with the zoom or distance key (it can be set in the" & vbNewLine & "settings tab)."
        CBox_DustPatch.Text = "Fix the rendering of dust particles"
        Dsr_DustPatch.Text = "Corrects the direction of dust particles flying from under the wheels of cars."

        CBox_MirrorsFix.Text = "Fix flickering mirrors"
        Dsr_MirrorsFix.Text = "Disables the rendering of side rear-view mirrors if the camera rotation key is not pressed." & vbNewLine & "This is important when the game is running in 16:9 resolutions."

        'page_mods
        CBox_VehicleMod.Text = "Turn signals"
        Dsr_VehicleMod.Text = "Adds working turn indicators to both the player's car and the rest of the game vehicles." & vbNewLine & "Turn signals also work on computer-controlled cars."

        CBox_InteriorMod.Text = "Additional indicators in the interiors"
        Dsr_InteriorMod.Text = "Adds working warning lights to some vehicle interiors."

        CBox_UpgradesMod.Text = "New gearboxes"
        Dsr_UpgradesMod.Text = "A modification that changes the gearbox on the player's car to a faster one if an accelerated" & vbNewLine & "engine is installed. Not all vehicles have new gearboxes."

        CBox_TabloMod.Text = "Real-time top panel updates"
        Dsr_TabloMod.Text = "Disables the delay in updating the values of the upper interface panel. If enabled, icons like" & vbNewLine & "the handbrake or fuel level will no longer blink."

        CBox_RainMod.Text = "Falling raindrops when first-person view enabled"
        Dsr_RainMod.Text = "Enables rendering of falling raindrops if the view from the interior is enabled. It may reduce" & vbNewLine & "the game perfomance."

        'page_settings
        GroupBox_Controls.Text = "Controls"
        LblCtrl_ModifierKey.Text = "Camera modifier:"
        LblCtrl_TurnSignalRKey.Text = "Right turn signal key:"
        LblCtrl_TurnSignalLKey.Text = "Left turn signal key:"
        LblCtrl_TurnSignalHKey.Text = "Hazard lights key:"

        Lbl_D2GIScrFormat.Text = "Screenshots format:"
        Lbl_D2GI_VSync.Text = "Vertical sync:"

        'page_about
        Lbl_about1.Text = "King of the Road Patch" & vbNewLine & "Version 1.00"
        Lbl_about2.Text = "This patch uses:"

        Lbl_about_ASILoader.Text = "* Ultimate ASI Loader by ThirteenAG"
        Lbl_about_D2DInputWrapper.Text = "* CPatch.h from D2DInputWrapper by Voron295"
        Lbl_about_Detour.Text = "* Detour project files by Zer0Mem0ry"
        Lbl_about_D2GI.Text = "* D2GIv2 (based on D2GI by REDPOWAR and NewEXE)"

        Lbl_about_author.Text = "The author of the patch is aleko2144"

        Lbl_about_thanks.Text = "Thanks to:"
        Lbl_about_t1.Text = "* Duude92 - author of a script that disables LOD in b3d files, the author of the tools" & vbNewLine & "for the game"
        Lbl_about_t2.Text = "* Voron295 - author of many useful tools and useful information about the game, which" & vbNewLine & "simplified the development of the patch"
        Lbl_about_t3.Text = "* AlexKimov - author of many useful tools and descriptions of game formats that have" & vbNewLine & "simplified patch development"
        Lbl_about_t4.Text = "* LabVaKars - author of handy tools for working with game resources"
        Lbl_about_t5.Text = "* Victor R. - advices for developing patch"
        Lbl_about_t6.Text = "* And also to the members of the vk.com/rnr_mods community and the Telegram channel :)"
    End Sub
End Class
