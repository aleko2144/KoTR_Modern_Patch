Module Module_Win32Functions
    Public Declare Function GetPrivateProfileStringA Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer, ByVal lpFileName As String) As Integer
    Public Declare Function WritePrivateProfileStringA Lib "Kernel32" Alias "WritePrivateProfileStringA" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpString As String, ByVal lpFileName As String) As Integer
    Public Declare Function GetPrivateProfileIntA Lib "kernel32" Alias "GetPrivateProfileIntA" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal nDefault As Integer, ByVal lpFileName As String) As Integer

    Public Sub WritePrivateProfileIntA(ByVal lpAppName As String, ByVal lpKeyName As String, ByVal nValue As Integer, ByVal lpFileName As String)
        WritePrivateProfileStringA(lpAppName, lpKeyName, nValue.ToString(), lpFileName)
    End Sub
End Module
