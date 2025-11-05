<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form_Main
    Inherits System.Windows.Forms.Form

    'Форма переопределяет dispose для очистки списка компонентов.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Является обязательной для конструктора форм Windows Forms
    Private components As System.ComponentModel.IContainer

    'Примечание: следующая процедура является обязательной для конструктора форм Windows Forms
    'Для ее изменения используйте конструктор форм Windows Form.  
    'Не изменяйте ее в редакторе исходного кода.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form_Main))
        Me.lbl_Version = New System.Windows.Forms.Label()
        Me.vk_link = New System.Windows.Forms.Label()
        Me.Btn_RunGame = New System.Windows.Forms.Button()
        Me.Btn_Exit = New System.Windows.Forms.Button()
        Me.TControl_UI = New System.Windows.Forms.TabControl()
        Me.page_patches = New System.Windows.Forms.TabPage()
        Me.Dsr_MirrorsFix = New System.Windows.Forms.Label()
        Me.CBox_MirrorsFix = New System.Windows.Forms.CheckBox()
        Me.Dsr_DustPatch = New System.Windows.Forms.Label()
        Me.CBox_DustPatch = New System.Windows.Forms.CheckBox()
        Me.Dsr_CameraMod = New System.Windows.Forms.Label()
        Me.CBox_CameraMod = New System.Windows.Forms.CheckBox()
        Me.Dsr_PhysicsMod = New System.Windows.Forms.Label()
        Me.CBox_CollisionMod = New System.Windows.Forms.CheckBox()
        Me.CBox_PhysicsMod = New System.Windows.Forms.CheckBox()
        Me.Dsr_CollisionMod = New System.Windows.Forms.Label()
        Me.ShapeContainer1 = New Microsoft.VisualBasic.PowerPacks.ShapeContainer()
        Me.LineShape4 = New Microsoft.VisualBasic.PowerPacks.LineShape()
        Me.LineShape3 = New Microsoft.VisualBasic.PowerPacks.LineShape()
        Me.LineShape2 = New Microsoft.VisualBasic.PowerPacks.LineShape()
        Me.LineShape1 = New Microsoft.VisualBasic.PowerPacks.LineShape()
        Me.page_mods = New System.Windows.Forms.TabPage()
        Me.Dsr_RainMod = New System.Windows.Forms.Label()
        Me.CBox_RainMod = New System.Windows.Forms.CheckBox()
        Me.Dsr_TabloMod = New System.Windows.Forms.Label()
        Me.CBox_TabloMod = New System.Windows.Forms.CheckBox()
        Me.Dsr_UpgradesMod = New System.Windows.Forms.Label()
        Me.CBox_UpgradesMod = New System.Windows.Forms.CheckBox()
        Me.Dsr_InteriorMod = New System.Windows.Forms.Label()
        Me.CBox_VehicleMod = New System.Windows.Forms.CheckBox()
        Me.CBox_InteriorMod = New System.Windows.Forms.CheckBox()
        Me.Dsr_VehicleMod = New System.Windows.Forms.Label()
        Me.ShapeContainer2 = New Microsoft.VisualBasic.PowerPacks.ShapeContainer()
        Me.LineShape8 = New Microsoft.VisualBasic.PowerPacks.LineShape()
        Me.LineShape7 = New Microsoft.VisualBasic.PowerPacks.LineShape()
        Me.LineShape6 = New Microsoft.VisualBasic.PowerPacks.LineShape()
        Me.LineShape5 = New Microsoft.VisualBasic.PowerPacks.LineShape()
        Me.page_settings = New System.Windows.Forms.TabPage()
        Me.GBox_D2GI = New System.Windows.Forms.GroupBox()
        Me.CBox_VSync = New System.Windows.Forms.CheckBox()
        Me.Lbl_D2GI_VSync = New System.Windows.Forms.Label()
        Me.CBox_D2GIScrFormat = New System.Windows.Forms.ComboBox()
        Me.Lbl_D2GIScrFormat = New System.Windows.Forms.Label()
        Me.GroupBox_Controls = New System.Windows.Forms.GroupBox()
        Me.TBox_TurnSignalHKey = New System.Windows.Forms.TextBox()
        Me.TBox_TurnSignalLKey = New System.Windows.Forms.TextBox()
        Me.TBox_TurnSignalRKey = New System.Windows.Forms.TextBox()
        Me.TBox_ModifierKey = New System.Windows.Forms.TextBox()
        Me.LblCtrl_TurnSignalHKey = New System.Windows.Forms.Label()
        Me.LblCtrl_TurnSignalLKey = New System.Windows.Forms.Label()
        Me.LblCtrl_TurnSignalRKey = New System.Windows.Forms.Label()
        Me.LblCtrl_ModifierKey = New System.Windows.Forms.Label()
        Me.page_about = New System.Windows.Forms.TabPage()
        Me.Lbl_about_t6 = New System.Windows.Forms.Label()
        Me.Lbl_about_t5 = New System.Windows.Forms.Label()
        Me.Lbl_about_t4 = New System.Windows.Forms.Label()
        Me.Lbl_about_t3 = New System.Windows.Forms.Label()
        Me.Lbl_about_t2 = New System.Windows.Forms.Label()
        Me.Lbl_about_t1 = New System.Windows.Forms.Label()
        Me.Lbl_about_thanks = New System.Windows.Forms.Label()
        Me.Lbl_about_author = New System.Windows.Forms.Label()
        Me.Lbl_about_Detour = New System.Windows.Forms.Label()
        Me.Lbl_about_D2DInputWrapper = New System.Windows.Forms.Label()
        Me.Lbl_about_ASILoader = New System.Windows.Forms.Label()
        Me.Lbl_about2 = New System.Windows.Forms.Label()
        Me.Lbl_about1 = New System.Windows.Forms.Label()
        Me.Lbl_about_D2GI = New System.Windows.Forms.Label()
        Me.TControl_UI.SuspendLayout()
        Me.page_patches.SuspendLayout()
        Me.page_mods.SuspendLayout()
        Me.page_settings.SuspendLayout()
        Me.GBox_D2GI.SuspendLayout()
        Me.GroupBox_Controls.SuspendLayout()
        Me.page_about.SuspendLayout()
        Me.SuspendLayout()
        '
        'lbl_Version
        '
        Me.lbl_Version.AutoSize = True
        Me.lbl_Version.Location = New System.Drawing.Point(2, 414)
        Me.lbl_Version.Name = "lbl_Version"
        Me.lbl_Version.Size = New System.Drawing.Size(288, 13)
        Me.lbl_Version.TabIndex = 11
        Me.lbl_Version.Text = "Версия 1.00 (2025.11.04). Обновления и новости здесь:"
        '
        'vk_link
        '
        Me.vk_link.AutoSize = True
        Me.vk_link.Cursor = System.Windows.Forms.Cursors.Hand
        Me.vk_link.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, CType(204, Byte))
        Me.vk_link.ForeColor = System.Drawing.SystemColors.Highlight
        Me.vk_link.Location = New System.Drawing.Point(289, 414)
        Me.vk_link.Name = "vk_link"
        Me.vk_link.Size = New System.Drawing.Size(90, 13)
        Me.vk_link.TabIndex = 10
        Me.vk_link.Text = "vk.com/rnr_mods"
        '
        'Btn_RunGame
        '
        Me.Btn_RunGame.Location = New System.Drawing.Point(2, 386)
        Me.Btn_RunGame.Name = "Btn_RunGame"
        Me.Btn_RunGame.Size = New System.Drawing.Size(225, 23)
        Me.Btn_RunGame.TabIndex = 9
        Me.Btn_RunGame.Text = "Запустить игру"
        Me.Btn_RunGame.UseVisualStyleBackColor = True
        '
        'Btn_Exit
        '
        Me.Btn_Exit.Location = New System.Drawing.Point(230, 386)
        Me.Btn_Exit.Name = "Btn_Exit"
        Me.Btn_Exit.Size = New System.Drawing.Size(225, 23)
        Me.Btn_Exit.TabIndex = 8
        Me.Btn_Exit.Text = "Выйти"
        Me.Btn_Exit.UseVisualStyleBackColor = True
        '
        'TControl_UI
        '
        Me.TControl_UI.Controls.Add(Me.page_patches)
        Me.TControl_UI.Controls.Add(Me.page_mods)
        Me.TControl_UI.Controls.Add(Me.page_settings)
        Me.TControl_UI.Controls.Add(Me.page_about)
        Me.TControl_UI.Location = New System.Drawing.Point(2, 2)
        Me.TControl_UI.Name = "TControl_UI"
        Me.TControl_UI.SelectedIndex = 0
        Me.TControl_UI.Size = New System.Drawing.Size(453, 378)
        Me.TControl_UI.TabIndex = 12
        '
        'page_patches
        '
        Me.page_patches.BackColor = System.Drawing.SystemColors.Control
        Me.page_patches.Controls.Add(Me.Dsr_MirrorsFix)
        Me.page_patches.Controls.Add(Me.CBox_MirrorsFix)
        Me.page_patches.Controls.Add(Me.Dsr_DustPatch)
        Me.page_patches.Controls.Add(Me.CBox_DustPatch)
        Me.page_patches.Controls.Add(Me.Dsr_CameraMod)
        Me.page_patches.Controls.Add(Me.CBox_CameraMod)
        Me.page_patches.Controls.Add(Me.Dsr_PhysicsMod)
        Me.page_patches.Controls.Add(Me.CBox_CollisionMod)
        Me.page_patches.Controls.Add(Me.CBox_PhysicsMod)
        Me.page_patches.Controls.Add(Me.Dsr_CollisionMod)
        Me.page_patches.Controls.Add(Me.ShapeContainer1)
        Me.page_patches.Location = New System.Drawing.Point(4, 22)
        Me.page_patches.Name = "page_patches"
        Me.page_patches.Padding = New System.Windows.Forms.Padding(3)
        Me.page_patches.Size = New System.Drawing.Size(445, 352)
        Me.page_patches.TabIndex = 0
        Me.page_patches.Text = "Патчи"
        '
        'Dsr_MirrorsFix
        '
        Me.Dsr_MirrorsFix.AutoSize = True
        Me.Dsr_MirrorsFix.Location = New System.Drawing.Point(4, 295)
        Me.Dsr_MirrorsFix.Name = "Dsr_MirrorsFix"
        Me.Dsr_MirrorsFix.Size = New System.Drawing.Size(405, 26)
        Me.Dsr_MirrorsFix.TabIndex = 23
        Me.Dsr_MirrorsFix.Text = "Отключает отрисовку боковых зеркал заднего вида, если не нажата клавиша" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "поворота" & _
    " камеры. Актуально при работе игры в разрешениях формата 16:9."
        '
        'CBox_MirrorsFix
        '
        Me.CBox_MirrorsFix.AutoSize = True
        Me.CBox_MirrorsFix.Location = New System.Drawing.Point(5, 274)
        Me.CBox_MirrorsFix.Name = "CBox_MirrorsFix"
        Me.CBox_MirrorsFix.Size = New System.Drawing.Size(190, 17)
        Me.CBox_MirrorsFix.TabIndex = 22
        Me.CBox_MirrorsFix.Text = "Исправить мерцающие зеркала"
        Me.CBox_MirrorsFix.UseVisualStyleBackColor = True
        '
        'Dsr_DustPatch
        '
        Me.Dsr_DustPatch.AutoSize = True
        Me.Dsr_DustPatch.Location = New System.Drawing.Point(5, 245)
        Me.Dsr_DustPatch.Name = "Dsr_DustPatch"
        Me.Dsr_DustPatch.Size = New System.Drawing.Size(403, 13)
        Me.Dsr_DustPatch.TabIndex = 21
        Me.Dsr_DustPatch.Text = "Корректирует направление частиц пыли, летящих из-под колёс автомобилей."
        '
        'CBox_DustPatch
        '
        Me.CBox_DustPatch.AutoSize = True
        Me.CBox_DustPatch.Location = New System.Drawing.Point(6, 224)
        Me.CBox_DustPatch.Name = "CBox_DustPatch"
        Me.CBox_DustPatch.Size = New System.Drawing.Size(202, 17)
        Me.CBox_DustPatch.TabIndex = 20
        Me.CBox_DustPatch.Text = "Исправить отрисовку частиц пыли"
        Me.CBox_DustPatch.UseVisualStyleBackColor = True
        '
        'Dsr_CameraMod
        '
        Me.Dsr_CameraMod.AutoSize = True
        Me.Dsr_CameraMod.Location = New System.Drawing.Point(5, 168)
        Me.Dsr_CameraMod.Name = "Dsr_CameraMod"
        Me.Dsr_CameraMod.Size = New System.Drawing.Size(397, 39)
        Me.Dsr_CameraMod.TabIndex = 19
        Me.Dsr_CameraMod.Text = "Исправляет ""улетающую"" камеру при виде снаружи. Камера перемещается" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "быстрее, есл" & _
    "и зажата клавиша-модификатор совместно с клавишей" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "приближения или отдаления (мо" & _
    "жно задать в разделе настроек)."
        '
        'CBox_CameraMod
        '
        Me.CBox_CameraMod.AutoSize = True
        Me.CBox_CameraMod.Location = New System.Drawing.Point(6, 147)
        Me.CBox_CameraMod.Name = "CBox_CameraMod"
        Me.CBox_CameraMod.Size = New System.Drawing.Size(244, 17)
        Me.CBox_CameraMod.TabIndex = 18
        Me.CBox_CameraMod.Text = "Фиксированная камера при виде снаружи"
        Me.CBox_CameraMod.UseVisualStyleBackColor = True
        '
        'Dsr_PhysicsMod
        '
        Me.Dsr_PhysicsMod.AutoSize = True
        Me.Dsr_PhysicsMod.Location = New System.Drawing.Point(5, 91)
        Me.Dsr_PhysicsMod.Name = "Dsr_PhysicsMod"
        Me.Dsr_PhysicsMod.Size = New System.Drawing.Size(415, 39)
        Me.Dsr_PhysicsMod.TabIndex = 16
        Me.Dsr_PhysicsMod.Text = "Экспериментальная модификация. Снижает инертность автопоездов в режиме" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & """симулято" & _
    "р"". В ""аркаде"" слегка уменьшает заносы полуприцепов. При низком" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "FPS даёт обратн" & _
    "ый эффект."
        '
        'CBox_CollisionMod
        '
        Me.CBox_CollisionMod.AutoSize = True
        Me.CBox_CollisionMod.Location = New System.Drawing.Point(6, 6)
        Me.CBox_CollisionMod.Name = "CBox_CollisionMod"
        Me.CBox_CollisionMod.Size = New System.Drawing.Size(235, 17)
        Me.CBox_CollisionMod.TabIndex = 13
        Me.CBox_CollisionMod.Text = "Перенастройка обработки столкновений"
        Me.CBox_CollisionMod.UseVisualStyleBackColor = True
        '
        'CBox_PhysicsMod
        '
        Me.CBox_PhysicsMod.AutoSize = True
        Me.CBox_PhysicsMod.Location = New System.Drawing.Point(6, 70)
        Me.CBox_PhysicsMod.Name = "CBox_PhysicsMod"
        Me.CBox_PhysicsMod.Size = New System.Drawing.Size(290, 17)
        Me.CBox_PhysicsMod.TabIndex = 15
        Me.CBox_PhysicsMod.Text = "Перенастройка параметров движения автопоездов"
        Me.CBox_PhysicsMod.UseVisualStyleBackColor = True
        '
        'Dsr_CollisionMod
        '
        Me.Dsr_CollisionMod.AutoSize = True
        Me.Dsr_CollisionMod.Location = New System.Drawing.Point(5, 27)
        Me.Dsr_CollisionMod.Name = "Dsr_CollisionMod"
        Me.Dsr_CollisionMod.Size = New System.Drawing.Size(423, 26)
        Me.Dsr_CollisionMod.TabIndex = 14
        Me.Dsr_CollisionMod.Text = "Частично исправляет ""залипания"" транспорта при столкновениях. Если активно," & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "то о" & _
    "тключается возможность сбивать деревья в игре."
        '
        'ShapeContainer1
        '
        Me.ShapeContainer1.Location = New System.Drawing.Point(3, 3)
        Me.ShapeContainer1.Margin = New System.Windows.Forms.Padding(0)
        Me.ShapeContainer1.Name = "ShapeContainer1"
        Me.ShapeContainer1.Shapes.AddRange(New Microsoft.VisualBasic.PowerPacks.Shape() {Me.LineShape4, Me.LineShape3, Me.LineShape2, Me.LineShape1})
        Me.ShapeContainer1.Size = New System.Drawing.Size(439, 346)
        Me.ShapeContainer1.TabIndex = 17
        Me.ShapeContainer1.TabStop = False
        '
        'LineShape4
        '
        Me.LineShape4.BorderColor = System.Drawing.SystemColors.ScrollBar
        Me.LineShape4.Enabled = False
        Me.LineShape4.Name = "LineShape4"
        Me.LineShape4.X1 = 4
        Me.LineShape4.X2 = 434
        Me.LineShape4.Y1 = 262
        Me.LineShape4.Y2 = 262
        '
        'LineShape3
        '
        Me.LineShape3.BorderColor = System.Drawing.SystemColors.ScrollBar
        Me.LineShape3.Enabled = False
        Me.LineShape3.Name = "LineShape3"
        Me.LineShape3.X1 = 4
        Me.LineShape3.X2 = 434
        Me.LineShape3.Y1 = 212
        Me.LineShape3.Y2 = 212
        '
        'LineShape2
        '
        Me.LineShape2.BorderColor = System.Drawing.SystemColors.ScrollBar
        Me.LineShape2.Enabled = False
        Me.LineShape2.Name = "LineShape2"
        Me.LineShape2.X1 = 4
        Me.LineShape2.X2 = 434
        Me.LineShape2.Y1 = 134
        Me.LineShape2.Y2 = 134
        '
        'LineShape1
        '
        Me.LineShape1.BorderColor = System.Drawing.SystemColors.ScrollBar
        Me.LineShape1.Enabled = False
        Me.LineShape1.Name = "LineShape1"
        Me.LineShape1.X1 = 5
        Me.LineShape1.X2 = 435
        Me.LineShape1.Y1 = 57
        Me.LineShape1.Y2 = 57
        '
        'page_mods
        '
        Me.page_mods.BackColor = System.Drawing.SystemColors.Control
        Me.page_mods.Controls.Add(Me.Dsr_RainMod)
        Me.page_mods.Controls.Add(Me.CBox_RainMod)
        Me.page_mods.Controls.Add(Me.Dsr_TabloMod)
        Me.page_mods.Controls.Add(Me.CBox_TabloMod)
        Me.page_mods.Controls.Add(Me.Dsr_UpgradesMod)
        Me.page_mods.Controls.Add(Me.CBox_UpgradesMod)
        Me.page_mods.Controls.Add(Me.Dsr_InteriorMod)
        Me.page_mods.Controls.Add(Me.CBox_VehicleMod)
        Me.page_mods.Controls.Add(Me.CBox_InteriorMod)
        Me.page_mods.Controls.Add(Me.Dsr_VehicleMod)
        Me.page_mods.Controls.Add(Me.ShapeContainer2)
        Me.page_mods.Location = New System.Drawing.Point(4, 22)
        Me.page_mods.Name = "page_mods"
        Me.page_mods.Padding = New System.Windows.Forms.Padding(3)
        Me.page_mods.Size = New System.Drawing.Size(445, 352)
        Me.page_mods.TabIndex = 1
        Me.page_mods.Text = "Модификации"
        '
        'Dsr_RainMod
        '
        Me.Dsr_RainMod.AutoSize = True
        Me.Dsr_RainMod.Location = New System.Drawing.Point(4, 280)
        Me.Dsr_RainMod.Name = "Dsr_RainMod"
        Me.Dsr_RainMod.Size = New System.Drawing.Size(431, 26)
        Me.Dsr_RainMod.TabIndex = 33
        Me.Dsr_RainMod.Text = "Включает отрисовку падающих капель дождя, если включен вид из салона. Может" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "сниз" & _
    "ить быстродействие игры."
        '
        'CBox_RainMod
        '
        Me.CBox_RainMod.AutoSize = True
        Me.CBox_RainMod.Location = New System.Drawing.Point(5, 259)
        Me.CBox_RainMod.Name = "CBox_RainMod"
        Me.CBox_RainMod.Size = New System.Drawing.Size(251, 17)
        Me.CBox_RainMod.TabIndex = 32
        Me.CBox_RainMod.Text = "Падающие капли дождя при виде из салона"
        Me.CBox_RainMod.UseVisualStyleBackColor = True
        '
        'Dsr_TabloMod
        '
        Me.Dsr_TabloMod.AutoSize = True
        Me.Dsr_TabloMod.Location = New System.Drawing.Point(5, 217)
        Me.Dsr_TabloMod.Name = "Dsr_TabloMod"
        Me.Dsr_TabloMod.Size = New System.Drawing.Size(418, 26)
        Me.Dsr_TabloMod.TabIndex = 31
        Me.Dsr_TabloMod.Text = "Отключает задержку обновления значений верхней панели интерфейса. Если" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "включено," & _
    " то значки вроде ручника или уровня топлива больше не будут мигать."
        '
        'CBox_TabloMod
        '
        Me.CBox_TabloMod.AutoSize = True
        Me.CBox_TabloMod.Location = New System.Drawing.Point(6, 196)
        Me.CBox_TabloMod.Name = "CBox_TabloMod"
        Me.CBox_TabloMod.Size = New System.Drawing.Size(280, 17)
        Me.CBox_TabloMod.TabIndex = 30
        Me.CBox_TabloMod.Text = "Обновление верхней панели в реальном времени"
        Me.CBox_TabloMod.UseVisualStyleBackColor = True
        '
        'Dsr_UpgradesMod
        '
        Me.Dsr_UpgradesMod.AutoSize = True
        Me.Dsr_UpgradesMod.Location = New System.Drawing.Point(5, 141)
        Me.Dsr_UpgradesMod.Name = "Dsr_UpgradesMod"
        Me.Dsr_UpgradesMod.Size = New System.Drawing.Size(414, 39)
        Me.Dsr_UpgradesMod.TabIndex = 29
        Me.Dsr_UpgradesMod.Text = "Модификация, меняющая коробку переключения передач на машине игрока на" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "более ско" & _
    "ростную, если установлен форсированный двигатель. Новые КПП" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "имеются не у всех а" & _
    "втомобилей."
        '
        'CBox_UpgradesMod
        '
        Me.CBox_UpgradesMod.AutoSize = True
        Me.CBox_UpgradesMod.Location = New System.Drawing.Point(6, 120)
        Me.CBox_UpgradesMod.Name = "CBox_UpgradesMod"
        Me.CBox_UpgradesMod.Size = New System.Drawing.Size(149, 17)
        Me.CBox_UpgradesMod.TabIndex = 28
        Me.CBox_UpgradesMod.Text = "Новые коробки передач"
        Me.CBox_UpgradesMod.UseVisualStyleBackColor = True
        '
        'Dsr_InteriorMod
        '
        Me.Dsr_InteriorMod.AutoSize = True
        Me.Dsr_InteriorMod.Location = New System.Drawing.Point(5, 91)
        Me.Dsr_InteriorMod.Name = "Dsr_InteriorMod"
        Me.Dsr_InteriorMod.Size = New System.Drawing.Size(319, 13)
        Me.Dsr_InteriorMod.TabIndex = 27
        Me.Dsr_InteriorMod.Text = "Добавляет рабочие сигнальные лампы в некоторые салоны."
        '
        'CBox_VehicleMod
        '
        Me.CBox_VehicleMod.AutoSize = True
        Me.CBox_VehicleMod.Location = New System.Drawing.Point(6, 6)
        Me.CBox_VehicleMod.Name = "CBox_VehicleMod"
        Me.CBox_VehicleMod.Size = New System.Drawing.Size(131, 17)
        Me.CBox_VehicleMod.TabIndex = 24
        Me.CBox_VehicleMod.Text = "Указатели поворота"
        Me.CBox_VehicleMod.UseVisualStyleBackColor = True
        '
        'CBox_InteriorMod
        '
        Me.CBox_InteriorMod.AutoSize = True
        Me.CBox_InteriorMod.Location = New System.Drawing.Point(6, 70)
        Me.CBox_InteriorMod.Name = "CBox_InteriorMod"
        Me.CBox_InteriorMod.Size = New System.Drawing.Size(222, 17)
        Me.CBox_InteriorMod.TabIndex = 26
        Me.CBox_InteriorMod.Text = "Дополнительная индикация в салонах"
        Me.CBox_InteriorMod.UseVisualStyleBackColor = True
        '
        'Dsr_VehicleMod
        '
        Me.Dsr_VehicleMod.AutoSize = True
        Me.Dsr_VehicleMod.Location = New System.Drawing.Point(5, 27)
        Me.Dsr_VehicleMod.Name = "Dsr_VehicleMod"
        Me.Dsr_VehicleMod.Size = New System.Drawing.Size(420, 26)
        Me.Dsr_VehicleMod.TabIndex = 25
        Me.Dsr_VehicleMod.Text = "Добавляет рабочие указатели поворота как на машину игрока, так и остальным" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "игров" & _
    "ым автомобилям."
        '
        'ShapeContainer2
        '
        Me.ShapeContainer2.Location = New System.Drawing.Point(3, 3)
        Me.ShapeContainer2.Margin = New System.Windows.Forms.Padding(0)
        Me.ShapeContainer2.Name = "ShapeContainer2"
        Me.ShapeContainer2.Shapes.AddRange(New Microsoft.VisualBasic.PowerPacks.Shape() {Me.LineShape8, Me.LineShape7, Me.LineShape6, Me.LineShape5})
        Me.ShapeContainer2.Size = New System.Drawing.Size(439, 346)
        Me.ShapeContainer2.TabIndex = 34
        Me.ShapeContainer2.TabStop = False
        '
        'LineShape8
        '
        Me.LineShape8.BorderColor = System.Drawing.SystemColors.ScrollBar
        Me.LineShape8.Enabled = False
        Me.LineShape8.Name = "LineShape8"
        Me.LineShape8.X1 = 4
        Me.LineShape8.X2 = 434
        Me.LineShape8.Y1 = 246
        Me.LineShape8.Y2 = 246
        '
        'LineShape7
        '
        Me.LineShape7.BorderColor = System.Drawing.SystemColors.ScrollBar
        Me.LineShape7.Enabled = False
        Me.LineShape7.Name = "LineShape7"
        Me.LineShape7.X1 = 4
        Me.LineShape7.X2 = 434
        Me.LineShape7.Y1 = 183
        Me.LineShape7.Y2 = 183
        '
        'LineShape6
        '
        Me.LineShape6.BorderColor = System.Drawing.SystemColors.ScrollBar
        Me.LineShape6.Enabled = False
        Me.LineShape6.Name = "LineShape6"
        Me.LineShape6.X1 = 4
        Me.LineShape6.X2 = 434
        Me.LineShape6.Y1 = 108
        Me.LineShape6.Y2 = 108
        '
        'LineShape5
        '
        Me.LineShape5.BorderColor = System.Drawing.SystemColors.ScrollBar
        Me.LineShape5.Enabled = False
        Me.LineShape5.Name = "LineShape5"
        Me.LineShape5.X1 = 5
        Me.LineShape5.X2 = 435
        Me.LineShape5.Y1 = 57
        Me.LineShape5.Y2 = 57
        '
        'page_settings
        '
        Me.page_settings.BackColor = System.Drawing.SystemColors.Control
        Me.page_settings.Controls.Add(Me.GBox_D2GI)
        Me.page_settings.Controls.Add(Me.GroupBox_Controls)
        Me.page_settings.Location = New System.Drawing.Point(4, 22)
        Me.page_settings.Name = "page_settings"
        Me.page_settings.Size = New System.Drawing.Size(445, 352)
        Me.page_settings.TabIndex = 3
        Me.page_settings.Text = "Настройки"
        '
        'GBox_D2GI
        '
        Me.GBox_D2GI.Controls.Add(Me.CBox_VSync)
        Me.GBox_D2GI.Controls.Add(Me.Lbl_D2GI_VSync)
        Me.GBox_D2GI.Controls.Add(Me.CBox_D2GIScrFormat)
        Me.GBox_D2GI.Controls.Add(Me.Lbl_D2GIScrFormat)
        Me.GBox_D2GI.Location = New System.Drawing.Point(6, 131)
        Me.GBox_D2GI.Name = "GBox_D2GI"
        Me.GBox_D2GI.Size = New System.Drawing.Size(433, 79)
        Me.GBox_D2GI.TabIndex = 1
        Me.GBox_D2GI.TabStop = False
        Me.GBox_D2GI.Text = "D2GI"
        '
        'CBox_VSync
        '
        Me.CBox_VSync.AutoSize = True
        Me.CBox_VSync.CheckAlign = System.Drawing.ContentAlignment.MiddleRight
        Me.CBox_VSync.Location = New System.Drawing.Point(256, 48)
        Me.CBox_VSync.Name = "CBox_VSync"
        Me.CBox_VSync.Size = New System.Drawing.Size(15, 14)
        Me.CBox_VSync.TabIndex = 2
        Me.CBox_VSync.UseVisualStyleBackColor = True
        '
        'Lbl_D2GI_VSync
        '
        Me.Lbl_D2GI_VSync.AutoSize = True
        Me.Lbl_D2GI_VSync.Location = New System.Drawing.Point(84, 48)
        Me.Lbl_D2GI_VSync.Name = "Lbl_D2GI_VSync"
        Me.Lbl_D2GI_VSync.Size = New System.Drawing.Size(162, 13)
        Me.Lbl_D2GI_VSync.TabIndex = 2
        Me.Lbl_D2GI_VSync.Text = "Вертикальная синхронизация:"
        '
        'CBox_D2GIScrFormat
        '
        Me.CBox_D2GIScrFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.CBox_D2GIScrFormat.Items.AddRange(New Object() {"jpg", "png", "bmp"})
        Me.CBox_D2GIScrFormat.Location = New System.Drawing.Point(256, 18)
        Me.CBox_D2GIScrFormat.Name = "CBox_D2GIScrFormat"
        Me.CBox_D2GIScrFormat.Size = New System.Drawing.Size(100, 21)
        Me.CBox_D2GIScrFormat.TabIndex = 1
        '
        'Lbl_D2GIScrFormat
        '
        Me.Lbl_D2GIScrFormat.AutoSize = True
        Me.Lbl_D2GIScrFormat.Location = New System.Drawing.Point(84, 21)
        Me.Lbl_D2GIScrFormat.Name = "Lbl_D2GIScrFormat"
        Me.Lbl_D2GIScrFormat.Size = New System.Drawing.Size(116, 13)
        Me.Lbl_D2GIScrFormat.TabIndex = 0
        Me.Lbl_D2GIScrFormat.Text = "Формат скриншотов:"
        '
        'GroupBox_Controls
        '
        Me.GroupBox_Controls.Controls.Add(Me.TBox_TurnSignalHKey)
        Me.GroupBox_Controls.Controls.Add(Me.TBox_TurnSignalLKey)
        Me.GroupBox_Controls.Controls.Add(Me.TBox_TurnSignalRKey)
        Me.GroupBox_Controls.Controls.Add(Me.TBox_ModifierKey)
        Me.GroupBox_Controls.Controls.Add(Me.LblCtrl_TurnSignalHKey)
        Me.GroupBox_Controls.Controls.Add(Me.LblCtrl_TurnSignalLKey)
        Me.GroupBox_Controls.Controls.Add(Me.LblCtrl_TurnSignalRKey)
        Me.GroupBox_Controls.Controls.Add(Me.LblCtrl_ModifierKey)
        Me.GroupBox_Controls.Location = New System.Drawing.Point(6, 3)
        Me.GroupBox_Controls.Name = "GroupBox_Controls"
        Me.GroupBox_Controls.Size = New System.Drawing.Size(433, 122)
        Me.GroupBox_Controls.TabIndex = 0
        Me.GroupBox_Controls.TabStop = False
        Me.GroupBox_Controls.Text = "Управление"
        '
        'TBox_TurnSignalHKey
        '
        Me.TBox_TurnSignalHKey.BackColor = System.Drawing.SystemColors.ControlLightLight
        Me.TBox_TurnSignalHKey.Location = New System.Drawing.Point(256, 94)
        Me.TBox_TurnSignalHKey.Name = "TBox_TurnSignalHKey"
        Me.TBox_TurnSignalHKey.ReadOnly = True
        Me.TBox_TurnSignalHKey.Size = New System.Drawing.Size(100, 20)
        Me.TBox_TurnSignalHKey.TabIndex = 8
        '
        'TBox_TurnSignalLKey
        '
        Me.TBox_TurnSignalLKey.BackColor = System.Drawing.SystemColors.ControlLightLight
        Me.TBox_TurnSignalLKey.Location = New System.Drawing.Point(256, 68)
        Me.TBox_TurnSignalLKey.Name = "TBox_TurnSignalLKey"
        Me.TBox_TurnSignalLKey.ReadOnly = True
        Me.TBox_TurnSignalLKey.Size = New System.Drawing.Size(100, 20)
        Me.TBox_TurnSignalLKey.TabIndex = 7
        '
        'TBox_TurnSignalRKey
        '
        Me.TBox_TurnSignalRKey.BackColor = System.Drawing.SystemColors.ControlLightLight
        Me.TBox_TurnSignalRKey.Location = New System.Drawing.Point(256, 42)
        Me.TBox_TurnSignalRKey.Name = "TBox_TurnSignalRKey"
        Me.TBox_TurnSignalRKey.ReadOnly = True
        Me.TBox_TurnSignalRKey.Size = New System.Drawing.Size(100, 20)
        Me.TBox_TurnSignalRKey.TabIndex = 6
        '
        'TBox_ModifierKey
        '
        Me.TBox_ModifierKey.BackColor = System.Drawing.SystemColors.ControlLightLight
        Me.TBox_ModifierKey.Location = New System.Drawing.Point(256, 16)
        Me.TBox_ModifierKey.Name = "TBox_ModifierKey"
        Me.TBox_ModifierKey.ReadOnly = True
        Me.TBox_ModifierKey.Size = New System.Drawing.Size(100, 20)
        Me.TBox_ModifierKey.TabIndex = 5
        '
        'LblCtrl_TurnSignalHKey
        '
        Me.LblCtrl_TurnSignalHKey.AutoSize = True
        Me.LblCtrl_TurnSignalHKey.Location = New System.Drawing.Point(84, 97)
        Me.LblCtrl_TurnSignalHKey.Name = "LblCtrl_TurnSignalHKey"
        Me.LblCtrl_TurnSignalHKey.Size = New System.Drawing.Size(139, 13)
        Me.LblCtrl_TurnSignalHKey.TabIndex = 4
        Me.LblCtrl_TurnSignalHKey.Text = "Аварийная сигнализация:"
        '
        'LblCtrl_TurnSignalLKey
        '
        Me.LblCtrl_TurnSignalLKey.AutoSize = True
        Me.LblCtrl_TurnSignalLKey.Location = New System.Drawing.Point(84, 71)
        Me.LblCtrl_TurnSignalLKey.Name = "LblCtrl_TurnSignalLKey"
        Me.LblCtrl_TurnSignalLKey.Size = New System.Drawing.Size(149, 13)
        Me.LblCtrl_TurnSignalLKey.TabIndex = 3
        Me.LblCtrl_TurnSignalLKey.Text = "Левый указатель поворота:"
        '
        'LblCtrl_TurnSignalRKey
        '
        Me.LblCtrl_TurnSignalRKey.AutoSize = True
        Me.LblCtrl_TurnSignalRKey.Location = New System.Drawing.Point(84, 45)
        Me.LblCtrl_TurnSignalRKey.Name = "LblCtrl_TurnSignalRKey"
        Me.LblCtrl_TurnSignalRKey.Size = New System.Drawing.Size(155, 13)
        Me.LblCtrl_TurnSignalRKey.TabIndex = 2
        Me.LblCtrl_TurnSignalRKey.Text = "Правый указатель поворота:"
        '
        'LblCtrl_ModifierKey
        '
        Me.LblCtrl_ModifierKey.AutoSize = True
        Me.LblCtrl_ModifierKey.Location = New System.Drawing.Point(84, 19)
        Me.LblCtrl_ModifierKey.Name = "LblCtrl_ModifierKey"
        Me.LblCtrl_ModifierKey.Size = New System.Drawing.Size(123, 13)
        Me.LblCtrl_ModifierKey.TabIndex = 1
        Me.LblCtrl_ModifierKey.Text = "Модификатор камеры:"
        '
        'page_about
        '
        Me.page_about.BackColor = System.Drawing.SystemColors.Control
        Me.page_about.Controls.Add(Me.Lbl_about_D2GI)
        Me.page_about.Controls.Add(Me.Lbl_about_t6)
        Me.page_about.Controls.Add(Me.Lbl_about_t5)
        Me.page_about.Controls.Add(Me.Lbl_about_t4)
        Me.page_about.Controls.Add(Me.Lbl_about_t3)
        Me.page_about.Controls.Add(Me.Lbl_about_t2)
        Me.page_about.Controls.Add(Me.Lbl_about_t1)
        Me.page_about.Controls.Add(Me.Lbl_about_thanks)
        Me.page_about.Controls.Add(Me.Lbl_about_author)
        Me.page_about.Controls.Add(Me.Lbl_about_Detour)
        Me.page_about.Controls.Add(Me.Lbl_about_D2DInputWrapper)
        Me.page_about.Controls.Add(Me.Lbl_about_ASILoader)
        Me.page_about.Controls.Add(Me.Lbl_about2)
        Me.page_about.Controls.Add(Me.Lbl_about1)
        Me.page_about.Location = New System.Drawing.Point(4, 22)
        Me.page_about.Name = "page_about"
        Me.page_about.Size = New System.Drawing.Size(445, 352)
        Me.page_about.TabIndex = 2
        Me.page_about.Text = "О программе"
        '
        'Lbl_about_t6
        '
        Me.Lbl_about_t6.AutoSize = True
        Me.Lbl_about_t6.Location = New System.Drawing.Point(8, 311)
        Me.Lbl_about_t6.Name = "Lbl_about_t6"
        Me.Lbl_about_t6.Size = New System.Drawing.Size(361, 13)
        Me.Lbl_about_t6.TabIndex = 12
        Me.Lbl_about_t6.Text = "* А также участникам группы vk.com/rnr_mods и канала в Телеграм :)"
        '
        'Lbl_about_t5
        '
        Me.Lbl_about_t5.AutoSize = True
        Me.Lbl_about_t5.Location = New System.Drawing.Point(8, 293)
        Me.Lbl_about_t5.Name = "Lbl_about_t5"
        Me.Lbl_about_t5.Size = New System.Drawing.Size(223, 13)
        Me.Lbl_about_t5.TabIndex = 11
        Me.Lbl_about_t5.Text = "* Виктор Р. - советы при разработке патча"
        '
        'Lbl_about_t4
        '
        Me.Lbl_about_t4.AutoSize = True
        Me.Lbl_about_t4.Location = New System.Drawing.Point(8, 275)
        Me.Lbl_about_t4.Name = "Lbl_about_t4"
        Me.Lbl_about_t4.Size = New System.Drawing.Size(379, 13)
        Me.Lbl_about_t4.TabIndex = 10
        Me.Lbl_about_t4.Text = "* LabVaKars - автор удобных инструментов для работы с ресурсами игры"
        '
        'Lbl_about_t3
        '
        Me.Lbl_about_t3.AutoSize = True
        Me.Lbl_about_t3.Location = New System.Drawing.Point(8, 244)
        Me.Lbl_about_t3.Name = "Lbl_about_t3"
        Me.Lbl_about_t3.Size = New System.Drawing.Size(411, 26)
        Me.Lbl_about_t3.TabIndex = 9
        Me.Lbl_about_t3.Text = "* AlexKimov - автор многих полезных инструментов и описаний форматов игры," & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "упрос" & _
    "тивших разработку патча"
        '
        'Lbl_about_t2
        '
        Me.Lbl_about_t2.AutoSize = True
        Me.Lbl_about_t2.Location = New System.Drawing.Point(7, 213)
        Me.Lbl_about_t2.Name = "Lbl_about_t2"
        Me.Lbl_about_t2.Size = New System.Drawing.Size(408, 26)
        Me.Lbl_about_t2.TabIndex = 8
        Me.Lbl_about_t2.Text = "* Voron295 - автор многих полезных инструментов и полезных данных об игре," & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "упрос" & _
    "тивших разработку патча"
        '
        'Lbl_about_t1
        '
        Me.Lbl_about_t1.AutoSize = True
        Me.Lbl_about_t1.Location = New System.Drawing.Point(7, 182)
        Me.Lbl_about_t1.Name = "Lbl_about_t1"
        Me.Lbl_about_t1.Size = New System.Drawing.Size(395, 26)
        Me.Lbl_about_t1.TabIndex = 7
        Me.Lbl_about_t1.Text = "* Duude92 - разработал скрипт, позволяющий отключить LOD в b3d-файлах," & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "автор инс" & _
    "трументов к игре"
        '
        'Lbl_about_thanks
        '
        Me.Lbl_about_thanks.AutoSize = True
        Me.Lbl_about_thanks.Location = New System.Drawing.Point(7, 164)
        Me.Lbl_about_thanks.Name = "Lbl_about_thanks"
        Me.Lbl_about_thanks.Size = New System.Drawing.Size(87, 13)
        Me.Lbl_about_thanks.TabIndex = 6
        Me.Lbl_about_thanks.Text = "Благодарности:"
        '
        'Lbl_about_author
        '
        Me.Lbl_about_author.AutoSize = True
        Me.Lbl_about_author.Location = New System.Drawing.Point(7, 142)
        Me.Lbl_about_author.Name = "Lbl_about_author"
        Me.Lbl_about_author.Size = New System.Drawing.Size(127, 13)
        Me.Lbl_about_author.TabIndex = 5
        Me.Lbl_about_author.Text = "Автор патча - aleko2144"
        '
        'Lbl_about_Detour
        '
        Me.Lbl_about_Detour.AutoSize = True
        Me.Lbl_about_Detour.Location = New System.Drawing.Point(7, 102)
        Me.Lbl_about_Detour.Name = "Lbl_about_Detour"
        Me.Lbl_about_Detour.Size = New System.Drawing.Size(297, 13)
        Me.Lbl_about_Detour.TabIndex = 4
        Me.Lbl_about_Detour.Text = "* Компоненты проекта Detour за авторством Zer0Mem0ry"
        '
        'Lbl_about_D2DInputWrapper
        '
        Me.Lbl_about_D2DInputWrapper.AutoSize = True
        Me.Lbl_about_D2DInputWrapper.Location = New System.Drawing.Point(7, 84)
        Me.Lbl_about_D2DInputWrapper.Name = "Lbl_about_D2DInputWrapper"
        Me.Lbl_about_D2DInputWrapper.Size = New System.Drawing.Size(334, 13)
        Me.Lbl_about_D2DInputWrapper.TabIndex = 3
        Me.Lbl_about_D2DInputWrapper.Text = "* CPatch.h из проекта D2DInputWrapper за авторством Voron295"
        '
        'Lbl_about_ASILoader
        '
        Me.Lbl_about_ASILoader.AutoSize = True
        Me.Lbl_about_ASILoader.Location = New System.Drawing.Point(7, 66)
        Me.Lbl_about_ASILoader.Name = "Lbl_about_ASILoader"
        Me.Lbl_about_ASILoader.Size = New System.Drawing.Size(243, 13)
        Me.Lbl_about_ASILoader.TabIndex = 2
        Me.Lbl_about_ASILoader.Text = "* Ultimate ASI Loader за авторством ThirteenAG"
        '
        'Lbl_about2
        '
        Me.Lbl_about2.AutoSize = True
        Me.Lbl_about2.Location = New System.Drawing.Point(7, 48)
        Me.Lbl_about2.Name = "Lbl_about2"
        Me.Lbl_about2.Size = New System.Drawing.Size(164, 13)
        Me.Lbl_about2.TabIndex = 1
        Me.Lbl_about2.Text = "В данном патче используются:"
        '
        'Lbl_about1
        '
        Me.Lbl_about1.AutoSize = True
        Me.Lbl_about1.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(204, Byte))
        Me.Lbl_about1.Location = New System.Drawing.Point(7, 7)
        Me.Lbl_about1.Name = "Lbl_about1"
        Me.Lbl_about1.Size = New System.Drawing.Size(249, 32)
        Me.Lbl_about1.TabIndex = 0
        Me.Lbl_about1.Text = "Патч к игре ""Дальнобойщики - 2""" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "Версия 1.00"
        '
        'Lbl_about_D2GI
        '
        Me.Lbl_about_D2GI.AutoSize = True
        Me.Lbl_about_D2GI.Location = New System.Drawing.Point(7, 120)
        Me.Lbl_about_D2GI.Name = "Lbl_about_D2GI"
        Me.Lbl_about_D2GI.Size = New System.Drawing.Size(327, 13)
        Me.Lbl_about_D2GI.TabIndex = 13
        Me.Lbl_about_D2GI.Text = "* D2GIv2 (на базе D2GI за авторством REDPOWAR и NewEXE)"
        '
        'Form_Main
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(457, 432)
        Me.Controls.Add(Me.TControl_UI)
        Me.Controls.Add(Me.lbl_Version)
        Me.Controls.Add(Me.vk_link)
        Me.Controls.Add(Me.Btn_RunGame)
        Me.Controls.Add(Me.Btn_Exit)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "Form_Main"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Конфигуратор"
        Me.TControl_UI.ResumeLayout(False)
        Me.page_patches.ResumeLayout(False)
        Me.page_patches.PerformLayout()
        Me.page_mods.ResumeLayout(False)
        Me.page_mods.PerformLayout()
        Me.page_settings.ResumeLayout(False)
        Me.GBox_D2GI.ResumeLayout(False)
        Me.GBox_D2GI.PerformLayout()
        Me.GroupBox_Controls.ResumeLayout(False)
        Me.GroupBox_Controls.PerformLayout()
        Me.page_about.ResumeLayout(False)
        Me.page_about.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents lbl_Version As System.Windows.Forms.Label
    Private WithEvents vk_link As System.Windows.Forms.Label
    Private WithEvents Btn_RunGame As System.Windows.Forms.Button
    Private WithEvents Btn_Exit As System.Windows.Forms.Button
    Friend WithEvents TControl_UI As System.Windows.Forms.TabControl
    Friend WithEvents page_patches As System.Windows.Forms.TabPage
    Friend WithEvents page_mods As System.Windows.Forms.TabPage
    Friend WithEvents page_about As System.Windows.Forms.TabPage
    Private WithEvents Dsr_PhysicsMod As System.Windows.Forms.Label
    Private WithEvents CBox_CollisionMod As System.Windows.Forms.CheckBox
    Private WithEvents CBox_PhysicsMod As System.Windows.Forms.CheckBox
    Private WithEvents Dsr_CollisionMod As System.Windows.Forms.Label
    Friend WithEvents ShapeContainer1 As Microsoft.VisualBasic.PowerPacks.ShapeContainer
    Friend WithEvents LineShape1 As Microsoft.VisualBasic.PowerPacks.LineShape
    Friend WithEvents page_settings As System.Windows.Forms.TabPage
    Private WithEvents Dsr_CameraMod As System.Windows.Forms.Label
    Private WithEvents CBox_CameraMod As System.Windows.Forms.CheckBox
    Friend WithEvents LineShape2 As Microsoft.VisualBasic.PowerPacks.LineShape
    Private WithEvents Dsr_DustPatch As System.Windows.Forms.Label
    Private WithEvents CBox_DustPatch As System.Windows.Forms.CheckBox
    Friend WithEvents LineShape3 As Microsoft.VisualBasic.PowerPacks.LineShape
    Private WithEvents Dsr_MirrorsFix As System.Windows.Forms.Label
    Private WithEvents CBox_MirrorsFix As System.Windows.Forms.CheckBox
    Friend WithEvents LineShape4 As Microsoft.VisualBasic.PowerPacks.LineShape
    Private WithEvents Dsr_RainMod As System.Windows.Forms.Label
    Private WithEvents CBox_RainMod As System.Windows.Forms.CheckBox
    Private WithEvents Dsr_TabloMod As System.Windows.Forms.Label
    Private WithEvents CBox_TabloMod As System.Windows.Forms.CheckBox
    Private WithEvents Dsr_UpgradesMod As System.Windows.Forms.Label
    Private WithEvents Dsr_InteriorMod As System.Windows.Forms.Label
    Private WithEvents CBox_VehicleMod As System.Windows.Forms.CheckBox
    Private WithEvents CBox_InteriorMod As System.Windows.Forms.CheckBox
    Private WithEvents Dsr_VehicleMod As System.Windows.Forms.Label
    Friend WithEvents ShapeContainer2 As Microsoft.VisualBasic.PowerPacks.ShapeContainer
    Friend WithEvents LineShape8 As Microsoft.VisualBasic.PowerPacks.LineShape
    Friend WithEvents LineShape7 As Microsoft.VisualBasic.PowerPacks.LineShape
    Friend WithEvents LineShape6 As Microsoft.VisualBasic.PowerPacks.LineShape
    Friend WithEvents LineShape5 As Microsoft.VisualBasic.PowerPacks.LineShape
    Private WithEvents CBox_UpgradesMod As System.Windows.Forms.CheckBox
    Friend WithEvents GroupBox_Controls As System.Windows.Forms.GroupBox
    Friend WithEvents LblCtrl_ModifierKey As System.Windows.Forms.Label
    Friend WithEvents TBox_TurnSignalHKey As System.Windows.Forms.TextBox
    Friend WithEvents TBox_TurnSignalRKey As System.Windows.Forms.TextBox
    Friend WithEvents TBox_ModifierKey As System.Windows.Forms.TextBox
    Friend WithEvents LblCtrl_TurnSignalHKey As System.Windows.Forms.Label
    Friend WithEvents LblCtrl_TurnSignalLKey As System.Windows.Forms.Label
    Friend WithEvents LblCtrl_TurnSignalRKey As System.Windows.Forms.Label
    Friend WithEvents TBox_TurnSignalLKey As System.Windows.Forms.TextBox
    Friend WithEvents GBox_D2GI As System.Windows.Forms.GroupBox
    Friend WithEvents CBox_D2GIScrFormat As System.Windows.Forms.ComboBox
    Friend WithEvents Lbl_D2GIScrFormat As System.Windows.Forms.Label
    Friend WithEvents Lbl_about1 As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_ASILoader As System.Windows.Forms.Label
    Friend WithEvents Lbl_about2 As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_Detour As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_D2DInputWrapper As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_t3 As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_t2 As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_t1 As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_thanks As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_author As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_t5 As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_t4 As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_t6 As System.Windows.Forms.Label
    Friend WithEvents CBox_VSync As System.Windows.Forms.CheckBox
    Friend WithEvents Lbl_D2GI_VSync As System.Windows.Forms.Label
    Friend WithEvents Lbl_about_D2GI As System.Windows.Forms.Label

End Class
