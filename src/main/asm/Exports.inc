extrn '__imp_ExitProcess' as ExitProcess:qword

extrn '__imp_GetProcessHeap' as GetProcessHeap:qword
extrn '__imp_GetLastError' as GetLastError:qword

extrn '__imp_HeapAlloc' as HeapAlloc:qword
extrn '__imp_HeapFree' as HeapFree:qword

include 'Exports/Letters.inc'
include 'Exports/Allocate.inc'
include 'Exports/List.inc'
include 'Exports/Numeric.inc'
include 'Exports/Flow.inc'
include 'Exports/NumericExpressions/NumericExpressions.inc'
include 'Exports/NumericExpressions/NumExpRefVal.inc'
include 'Exports/NumericExpressions/NumericParsing.inc'
include 'Exports/Storage/Storage.inc'
include 'Exports/Storage/StorageLetters.inc'
include 'Exports/Storage/StorageList.inc'
include 'Exports/Storage/StorageFlow.inc'
include 'Exports/Matching.inc'
include 'Exports/Replacement.inc'
include 'Exports/Time.inc'