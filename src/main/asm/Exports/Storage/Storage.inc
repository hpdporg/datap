extrn '__imp_CreateFileA' as CreateFile:qword
extrn '__imp_SetEndOfFile' as SetEndOfFile:qword
extrn '__imp_WriteFile' as WriteFile:qword
extrn '__imp_GetFileSize' as GetFileSize:qword
extrn '__imp_ReadFile' as ReadFile:qword
extrn '__imp_CloseHandle' as CloseHandle:qword
extrn '__imp_DeleteFileA' as DeleteFile:qword
extrn '__imp_FindFirstFileA' as FindFirstFile:qword
extrn '__imp_FindNextFileA' as FindNextFile:qword
extrn '__imp_FindClose' as FindClose:qword


;public storage.newFile as 'newFile'
;public storage.writeFile as 'writeFile'

public storage.new as 'newStorage'
public storage.defineRecordPath as 'defineRecordPath'
public storage.retrieve as 'retrieve'
public storage.storeLetters as 'storeLetters'
public storage.restoreLetters as 'restoreLetters'
public storage.retrieveRecordNames as 'retrieveRecordNames'
public storage.retrieveRecordNamesExtension as 'retrieveRecordNamesExtension'
public storage.removeRecord as 'removeRecord'
public storage.debugNum as 'debugNum'
public storage.debugLetters as 'debugLetters'
public storage.debugNumMsg as 'debugNumMsg'
public storage.debugLettersMsg as 'debugLettersMsg'