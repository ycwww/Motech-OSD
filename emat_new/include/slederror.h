/*! \file   slederror.h
 *  \author Harald Amrehn
 *  \date   23.06.2004
 *  \brief  Errornumber intervals for HMI Sl - Editor Widget
 *
 *  (C) Copyright Siemens AG 2004
*/

#if !defined(SL_ED_ERROR_H)
#define SL_ED_ERROR_H


#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00500000
//**ModuleName: HMI - SL Editor Widget
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Widget Editor
#define SLEDR_SUB_WIDGET_EDITOR    0x00008400
//**Name:Widget Sink
#define SLEDR_SUB_WIDGET_SINK      0x00008800
//**Name:Widget Block
#define SLEDR_SUB_WIDGET_BLOCK     0x00008C00
//**Name:Widget String
#define SLEDR_SUB_WIDGET_STR       0x00009000
//**Name:Widget Step
#define SLEDR_SUB_WIDGET_STEP      0x00009400
//**Name:Widget Interface
#define SLEDR_SUB_WIDGET_IF        0x00009800
//**Name:Widget NC-Block
#define SLEDR_SUB_WIDGET_PBLOCK    0x00009C00
//**Name:Widget NC-Step
#define SLEDR_SUB_WIDGET_PSTEP     0x0000A000
//**Name:Widget Step-Recognition
#define SLEDR_SUB_WIDGET_STEPREC   0x0000A400
//**Name:Widget NC-Communication
#define SLEDR_SUB_WIDGET_NCCOM     0x0000A800
//**Name:Widget Syntax Coloring
#define SLEDR_SUB_WIDGET_SYNTCOL   0x0000AC00
//**Name:Widget Others
#define SLEDR_SUB_WIDGET_OTHER     0x0000B000

//**Name:View Editor
#define SLEDR_SUB_VIEW_EDITOR      0x00010400
//**Name:View Sink
#define SLEDR_SUB_VIEW_SINK        0x00010800
//**Name:View Block
#define SLEDR_SUB_VIEW_BLOCK       0x00010C00
//**Name:View String
#define SLEDR_SUB_VIEW_STR         0x00011000
//**Name:View Step
#define SLEDR_SUB_VIEW_STEP        0x00011400
//**Name:View Interface
#define SLEDR_SUB_VIEW_IF          0x00011800
//**Name:View NC-Block
#define SLEDR_SUB_VIEW_PBLOCK      0x00011C00
//**Name:View NC-Step
#define SLEDR_SUB_VIEW_PSTEP       0x00012000
//**Name:View Step-Recognition
#define SLEDR_SUB_VIEW_STEPREC     0x00012400
//**Name:View NC-Communication
#define SLEDR_SUB_VIEW_NCCOM       0x00012800
//**Name:View Syntax Coloring
#define SLEDR_SUB_VIEW_SYNTCOL     0x00012C00
//**Name:View Others
#define SLEDR_SUB_VIEW_OTHER       0x00013000

//**Name:Function Editor
#define SLEDR_SUB_FUNC_EDITOR      0x00018400
//**Name:Function Sink
#define SLEDR_SUB_FUNC_SINK        0x00018800
//**Name:Function Block
#define SLEDR_SUB_FUNC_BLOCK       0x00018C00
//**Name:Function String
#define SLEDR_SUB_FUNC_STR         0x00019000
//**Name:Function Step
#define SLEDR_SUB_FUNC_STEP        0x00019400
//**Name:Function Interface
#define SLEDR_SUB_FUNC_IF          0x00019800
//**Name:Function NC-Block
#define SLEDR_SUB_FUNC_PBLOCK      0x00019C00
//**Name:Function NC-Step
#define SLEDR_SUB_FUNC_PSTEP       0x0001A000
//**Name:Function Step-Recognition
#define SLEDR_SUB_FUNC_STEPREC     0x0001A400
//**Name:Function NC-Communication
#define SLEDR_SUB_FUNC_NCCOM       0x0001A800
//**Name:Function Syntax Coloring
#define SLEDR_SUB_FUNC_SYNTCOL     0x0001AC00
//**Name:Function Others
#define SLEDR_SUB_FUNC_OTHER       0x0001B000
//**Name:Function Undo-Redo
#define SLEDR_SUB_FUNC_UNDO        0x0001C800

//**Name:FunctionMemory Editor
#define SLEDR_SUB_FUNCMEM_EDITOR   0x00020400
//**Name:FunctionMemory Sink
#define SLEDR_SUB_FUNCMEM_SINK     0x00020800
//**Name:FunctionMemory Block
#define SLEDR_SUB_FUNCMEM_BLOCK    0x00020C00
//**Name:FunctionMemory String
#define SLEDR_SUB_FUNCMEM_STR      0x00021000
//**Name:FunctionMemory Step
#define SLEDR_SUB_FUNCMEM_STEP     0x00021400
//**Name:FunctionMemory Interface
#define SLEDR_SUB_FUNCMEM_IF       0x00021800
//**Name:FunctionMemory NC-Block
#define SLEDR_SUB_FUNCMEM_PBLOCK   0x00021C00
//**Name:FunctionMemory NC-Step
#define SLEDR_SUB_FUNCMEM_PSTEP    0x00022000
//**Name:FunctionMemory Step-Recognition
#define SLEDR_SUB_FUNCMEM_STEPREC  0x00022400
//**Name:FunctionMemory NC-Communication
#define SLEDR_SUB_FUNCMEM_NCCOM    0x00022800
//**Name:FunctionMemory Syntax Coloring
#define SLEDR_SUB_FUNCMEM_SYNTCOL  0x00022C00
//**Name:FunctionMemory Others
#define SLEDR_SUB_FUNCMEM_OTHER    0x00023000

//**Name:Memory Editor
#define SLEDR_SUB_MEM_EDITOR       0x00028400
//**Name:Memory Sink
#define SLEDR_SUB_MEM_SINK         0x00028800
//**Name:Memory Block
#define SLEDR_SUB_MEM_BLOCK        0x00028C00
//**Name:Memory String
#define SLEDR_SUB_MEM_STR          0x00029000
//**Name:Memory Step
#define SLEDR_SUB_MEM_STEP         0x00029400
//**Name:Memory Interface
#define SLEDR_SUB_MEM_IF           0x00029800
//**Name:Memory NC-Block
#define SLEDR_SUB_MEM_PBLOCK       0x00029C00
//**Name:Memory NC-Step
#define SLEDR_SUB_MEM_PSTEP        0x0002A000
//**Name:Memory Step-Recognition
#define SLEDR_SUB_MEM_STEPREC      0x0002A400
//**Name:Memory NC-Communication
#define SLEDR_SUB_MEM_NCCOM        0x0002A800
//**Name:Memory Syntax Coloring
#define SLEDR_SUB_MEM_SYNTCOL      0x0002AC00
//**Name:Memory Others
#define SLEDR_SUB_MEM_OTHER        0x0002B000

//**Name:Helper Editor
#define SLEDR_SUB_HELP_EDITOR      0x00030400
//**Name:Helper Sink
#define SLEDR_SUB_HELP_SINK        0x00030800
//**Name:Helper Block
#define SLEDR_SUB_HELP_BLOCK       0x00030C00
//**Name:Helper String
#define SLEDR_SUB_HELP_STR         0x00031000
//**Name:Helper Step
#define SLEDR_SUB_HELP_STEP        0x00031400
//**Name:Helper Interface
#define SLEDR_SUB_HELP_IF          0x00031800
//**Name:Helper NC-Block
#define SLEDR_SUB_HELP_PBLOCK      0x00031C00
//**Name:Helper NC-Step
#define SLEDR_SUB_HELP_PSTEP       0x00032000
//**Name:Helper Step-Recognition
#define SLEDR_SUB_HELP_STEPREC     0x00032400
//**Name:Helper NC-Communication
#define SLEDR_SUB_HELP_NCCOM       0x00032800
//**Name:Helper Syntax Coloring
#define SLEDR_SUB_HELP_SYNTCOL     0x00032C00
//**Name:Helper Others
#define SLEDR_SUB_HELP_OTHER       0x00033000

//**Name:Step Logic Check
#define SLEDR_SUB_STEP_LOGIC_CHECK 0x00038400
//**Name:Step Logic Editor Functions
#define SLEDR_SUB_STEP_LOGIC_EDIT  0x00038800
//**ErrEndSubModules





///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:succeeded
#define SLEDR__OK                  0x00000000 
//**Text:succeeded and ready (asynchronous)
#define SLEDR__OK_READY            0x00000001 
//**Text:succeeded and recognized readonly area
#define SLEDR__OK_READONLY         0x00000002 
//**Text:canceled
#define SLEDR__OK_CANCELED         0x00000003 
//**Text:succeeded with no correction window on NC
#define SLEDR__OK_NC_NOCORWIN      0x00000004 
//**Text:succeeded with error on NC
#define SLEDR__OK_NC_FAILED        0x00000005 
//**Text:succeeded with no search pattern found
#define SLEDR__OK_NOTHING_FOUND    0x00000006
//**Text:succeeded, but found a long block
#define SLEDR__OK_LONG_BL_FOUND    0x00000007
//**Text:the cursor is at the bottom-right position, it is not possible to navigate right
#define SLEDR__FILE_BOTTOMRIGHT_POS 0x0000008
//**Text:opening the file has been stopped
#define SLEDR__OPEN_STOPPED        0x00000009
//**Text:drawing succeeded, but the widget didn't has to draw anything
#define SLEDR__OK_DIDNT_DRAW       0x00000010
//**Text:waitmark has been changed, as a result of ChangeBlocks
#define SLEDR__OK_WAITM_CHANGED    0x00000011
//**Text:failed
#define SLEDR__FAILED              0x80000001
//**Text:system error
#define SLEDR__SYSTEM_ERR          0x80000002
//**Text:failed by opening a file
#define SLEDR__OPENFILE_ERR        0x80000003
//**Text:failed by handling a temporary file
#define SLEDR__TMPFILE_ERR         0x80000004
//**Text:wrong argument
#define SLEDR__ARG_ERR             0x80000005
//**Text:memory failure
#define SLEDR__NOMEMORY_ERR        0x80000006
//**Text:not accepted at the current state
#define SLEDR__STATE_ERR           0x80000007
//**Text:length of block exceeds maximum
#define SLEDR__BLOCKLEN_ERR        0x80000008
//**Text:Cannot lock file
#define CANNOT_LOCK_FILE           0x80000009
//**Text:File is locked by another process
#define FILE_LOCKED                0x8000000A
//**Text:File is exclusively locked by another process
#define FILE_EXCL_LOCKED           0x8000000B
//**Text:timeout error through data transfer
#define SLEDR__COMTIMEOUT_ERR      0x8000000C
//**Text:readonly error
#define SLEDR__READONLY_ERR        0x8000000D
//**Text:readonly error referring to NC processing ($SEEKW-variable)
#define SLEDR__NCREADONLY_ERR      0x8000000E
//**Text:differently marked as expected
#define SLEDR__SELECTION_ERR       0x8000000F
//**Text:block number doesn't exist
#define SLEDR__BLOCKNUMBER_ERR     0x80000010
//**Text:not available for this object or not yet implemented
#define SLEDR__NOT_IMPL            0x80000011
//**Text:initialization of step recognition object failed
#define SLEDR__NO_STEPRECOG        0x80000012
//**Text:initialization of NCcom object failed
#define SLEDR__NO_NCCOM            0x80000013
//**Text:communication to NC failed
#define SLEDR__NO_COMMUNICATION    0x80000014
//**Text:network timeout
#define SLEDR__TIMEOUT             0x80000015
//**Text:NC-file doesn't exist
#define SLEDR__NO_NCFILE           0x80000016
//**Text:NC-file is binary
#define SLEDR__NCFILE_IS_BINARY    0x80000017
//**Text:edit session isn't initializied
#define SLEDR__NOT_INITIALIZED     0x80000018
//**Text:loading (opening) file is active
#define SLEDR__LOADING_IS_ACTIVE   0x80000019
//**Text:saving file is active
#define SLEDR__SAVING_IS_ACTIVE    0x8000001A
//**Text:printing is active
#define SLEDR__PRINTING_IS_ACTIVE  0x8000001B
//**Text:missing file name
#define SLEDR__MISSING_FILENAME    0x8000001C
//**Text:no regular file
#define SLEDR__NO_REGULAR_FILE     0x8000001D
//**Text:file not accessable
#define SLEDR__WRONG_FILE_STATUS   0x8000001E
//**Text:creating temporary file failed
#define SLEDR__CREATING_TMPFILE    0x8000001F
//**Text:creating temporary step format file failed
#define SLEDR__CREATING_TMPSTFILE  0x80000020
//**Text:opening file failed
#define SLEDR__OPEN_FILE           0x80000021
//**Text:opening temporary file failed
#define SLEDR__OPEN_TMPFILE        0x80000022
//**Text:closing file failed
#define SLEDR__CLOSE_FILE          0x80000023
//**Text:closing temporary file failed
#define SLEDR__CLOSE_TMPFILE       0x80000024
//**Text:closing temporary step format file failed
#define SLEDR__CLOSE_TMPSTFILE     0x80000025
//**Text:seek file position failed
#define SLEDR__SEEK_FILE           0x80000026
//**Text:reading from file failed
#define SLEDR__READING_FILE        0x80000027
//**Text:writing to temporary file failed
#define SLEDR__WRITING_TMPFILE     0x80000028
//**Text:deleting temporary file failed
#define SLEDR__DELETING_TMPFILE    0x80000029
//**Text:accessing cache failed
#define SLEDR__ACCESSING_CACHE     0x8000002A
//**Text:viewing first page failed
#define SLEDR__VIEWING_FIRST_PAGE  0x8000002B
//**Text:selecting block failed
#define SLEDR__SELECTING_BLOCK     0x8000002C
//**Text:a block exceeds the maximal length
#define SLEDR__BLOCK_TOO_LONG      0x8000002D
//**Text:getting interface pointer failed
#define SLEDR__CREATE_INSTANCE     0x8000002E
//**Text:getting interface pointer of view failed
#define SLEDR__CREATE_VIEWINST     0x8000002F
//**Text:getting interface pointer of function failed
#define SLEDR__CREATE_FUNCINST     0x80000030
//**Text:getting interface pointer of function memory failed
#define SLEDR__CREATE_FUNCMEMINST  0x80000031
//**Text:getting interface pointer of memory management failed
#define SLEDR__CREATE_MEMINST      0x80000032
//**Text:getting interface pointer of NC-communication failed
#define SLEDR__CREATE_NCCOMINST    0x80000033
//**Text:getting interface pointer of step recognition failed
#define SLEDR__CREATE_RECOGINST    0x80000034
//**Text:no interface pointer of view
#define SLEDR__NO_VIEWINST         0x80000035
//**Text:no interface pointer of function
#define SLEDR__NO_FUNCINST         0x80000036
//**Text:no interface pointer of function memory
#define SLEDR__NO_FUNCMEMINST      0x80000037
//**Text:no interface pointer of memory management
#define SLEDR__NO_MEMINST          0x80000038
//**Text:no interface pointer of NC-communication
#define SLEDR__NO_NCCOMINST        0x80000039
//**Text:no interface pointer of step recognition
#define SLEDR__NO_RECOGINST        0x8000003A
//**Text:no text marked
#define SLEDR__NOTHING_MARKED      0x8000003B
//**Text:other method currently busy
#define SLEDR__BUSY                0x8000003C
//**Text:no undo possible
#define SLEDR__NO_UNDO_POSSIBLE    0x8000003D
//**Text:no redo possible
#define SLEDR__NO_REDO_POSSIBLE    0x8000003E
//**Text:no paste possible
#define SLEDR__NO_PASTE_POSSIBLE   0x8000003F
//**Text:displayonly error
#define SLEDR__DISPLAYONLY_ERR     0x80000040
//**Text:no printer object existing
#define SLEDR__NO_PRINTERINST_ERR  0x80000041
//**Text:no interface pointer of callback class
#define SLEDR__NO_CALLBACKINST     0x80000042
//**Text:no interface pointer of editor widget class
#define SLEDR__NO_EDITORINST       0x80000043
//**Text:getting painter pointer failed
#define SLEDR__NO_PAINTERINST      0x80000044
//**Text:getting caret pointer failed
#define SLEDR__NO_CARETINST        0x80000045
//**Text:invalid caret line index
#define SLEDR__INV_CARETLINE_IDX   0x80000046
//**Text:invalid caret block number
#define SLEDR__INV_CARETBLOCK_NR   0x80000047
//**Text:invalid line attribute index
#define SLEDR__INV_LINEATTR_IDX    0x80000048
//**Text:empty line attribute array
#define SLEDR__EMPTY_LINEATTR_ARR  0x80000049
//**Text:initialization of syntax coloring object failed
#define SLEDR__NO_SYNTAXCOLORING   0x8000004A
//**Text:getting interface pointer of syntax coloring failed
#define SLEDR__CREATE_SYNTCOLINST  0x8000004B
//**Text:no interface pointer of syntax coloring
#define SLEDR__NO_SYNTCOLINST      0x8000004C
//**Text:access of property value failed
#define SLEDR__PROPERTY_ACC_ERR    0x8000004D
//**Text:no text segment in memory management
#define SLEDR__NO_SEGMENT_ERR      0x8000004E
//**Text:error on positioning or writing physical segment
#define SLEDR__SEGMENT_WRITE_ERR   0x8000004F
//**Text:no more blocks
#define SLEDR__NO_MORE_BLOCKS      0x80000050
//**Text:conversion error from string to long
#define SLEDR__ATOI_CONV_ERR       0x80000051
//**Text:MAXINT error
#define SLEDR__MAXINT_ERROR        0x80000052
//**Text:No Opened File
#define SLEDR__NO_OPEN_FILE        0x80000053
//**Text:ConfSizeOfMemorySegment too small
#define SLEDR__MEMSEGM_SMALL       0x80000054
//**Text:failed by saving a file
#define SLEDR__SAVEFILE_ERR        0x80000055
//**Text:setting of property failed
#define SLEDR__PROPERTY_SET_ERR    0x80000056
//**Text:hidden error
#define SLEDR__HIDDEN_ERR          0x80000057
//**Text:find-replace error
#define SLEDR__FINDREPLACE_ERR     0x80000058
//**Text:invalid search pattern
#define SLEDR__INV_PATTERN         0x80000059
//**Text:no step available
#define SLEDR__NO_STEP             0x8000005A
//**Text:ConfSizeOfMemorySegment can't be smaller than MaxBlockLen
#define SLEDR__MEMSEGM_ERR         0x8000005B
//**Text:not enough memory
#define SLEDR__NO_MEMORY           0x8000005C
//**Text:internal error
#define SLEDR__INTERNAL_ERR        0x8000005D
//**Text:clipboard is empty
#define SLEDR__EMPTY_CLIPBOARD     0x8000005E
//**Text:reading from temporary file failed
#define SLEDR__READING_TMPFILE     0x8000005F
//**Text:segment not present in cache
#define SLEDR__SEG_NOT_IN_CACHE    0x80000060
//**Text:cache is empty
#define SLEDR__EMPTY_CACHE         0x80000061
//**Text:invalid segment pointer
#define SLEDR__INV_SEG_PTR         0x80000062
//**Text:invalid cache
#define SLEDR__INV_CACHE           0x80000063
//**Text:invalid attribute list in cache
#define SLEDR__INV_ATTRIBLIST      0x80000064
//**Text:not enough blocks in segment
#define SLEDR__BLOCKS_IN_SEG       0x80000065
//**Text:no step attribute liste
#define SLEDR__NO_STEPATTR_LIST    0x80000066
//**Text:invalid step attribute pointer in cache
#define SLEDR__INV_STEPATTR_PTR    0x80000067
//**Text:invalid cache index
#define SLEDR__INV_CACHE_IDX       0x80000068
//**Text:No segment, no transition info
#define SLEDR__NO_SEG_NO_TRANSINF  0x80000069
//**Text:Block not found in segment
#define SLEDR__NO_BLOCK_IN_SEG     0x8000006A
//**Text:Getting mutex object failed
#define SLEDR__MUTEX_FAILED        0x8000006B
//**Text:Connect communication failed
#define SLEDR__CONNECT_FAILED      0x8000006C
//**Text:Disconnect communication failed
#define SLEDR__DISCONNECT_FAILED   0x8000006D
//**Text:Advise to SlCap failed
#define SLEDR__ADVISE_FAILED       0x8000006E
//**Text:Unadvise to SlCap failed
#define SLEDR__UNADVISE_FAILED     0x8000006F
//**Text:Not connected
#define SLEDR__NO_CONNECT          0x80000070
//**Text:Not opened
#define SLEDR__NO_OPEN             0x80000071
//**Text:Pressed key not allowed
#define SLEDR__NOT_ALLOWED         0x80000072
//**Text:Action not processed
#define SLEDR__NOT_PROCESSED       0x80000073
//**Text:Not all items provided
#define SLEDR__NOT_ALL_ITEMS_PROV  0x80000074
//**Text:Step too long (Step doesn't fit into one memory segment)
#define SLEDR__STEP_TOO_LONG       0x80000075
//**Text:The file contains \r as line ending
#define SLEDR__WRONG_LINE_ENDING   0x80000076
//**Text:NC isn't active, e.g. NC is booting or resetting
#define SLEDR__NC_NOT_ACTIVE       0x80000077
//**Text:reading from pipe failed
#define SLEDR__READING_PIPE        0x80000078
//**Text:writing to pipe failed
#define SLEDR__WRITING_PIPE        0x80000079
//**Text:writing file failed
#define SLEDR__WRITING_FILE        0x8000007A
//**Text:deleting file failed
#define SLEDR__DELETING_FILE       0x8000007B
//**Text:No NCG blocks
#define SLEDR__NO_NCG_BLOCKS       0x8000007C
//**Text:Step key not found in list
#define SLEDR__NO_STEPKEY_IN_LIST  0x8000007D
//**Text:No steps, no transition info
#define SLEDR__NO_STEPS_NO_TR_INF  0x8000007E
//**Text:No end key pattern before the next begin pattern
#define SLEDR__NO_END_KEY          0x8000007F
//**Text:No paint data inst
#define SLEDR__NO_PAINTDATAINST    0x80000080
//**Text:Empty line info item
#define SLEDR__EMPTY_LINEINFO_ITEM 0x80000081
//**Text:No more positions in paint data to left direction
#define SLEDR__NO_TOPLEFT_POS      0x80000082
//**Text:Inconsistent paint data
#define SLEDR__INCONSIST_PAINTDATA 0x80000083
//**Text:No more positions in paint data to right direction
#define SLEDR__NO_BOTTOM_RIGHT_POS 0x80000084
//**Text:No more lines in view
#define SLEDR__NO_MORE_LINES       0x80000085
//**Text:There are only gaps in view left
#define SLEDR__GAP_LINES           0x80000086
//**Text:There are no room for gaps in the view
#define SLEDR__NO_ROOM_FOR_GAPS    0x80000087
//**Text:Gaps cannot be inserted, invalid block number
#define SLEDR__NO_GAP_POSSIBLE     0x80000088
//**Text:The caret is not in the overhang area
#define SLEDR__CARET_NOTIN_OVERH   0x80000089
//**Text:No more positions in paint data upwards
#define SLEDR__NO_TOP_POS          0x8000008A
//**Text:No more positions in paint data downwards
#define SLEDR__NO_BOTTOM_POS       0x8000008B
//**Text:No empty lines were inserted
#define SLEDR__NO_EMPTY_LINES_INS  0x8000008C
//**Text:Invalid paint data
#define SLEDR__INV_PAINT_DATA      0x8000008D
//**Text:The view must be empty - full of gap lines
#define SLEDR__NO_EMPTY_VIEW       0x8000008E
//**Text:Caret is out of view
#define SLEDR__CARET_OUTOFVIEW     0x8000008F
//**Text:No caret line
#define SLEDR__NO_CARET_LINE       0x80000090
//**Text:Block number not in view
#define SLEDR__INV_VIEWBL_NR       0x80000091
//**Text:Tab stop to next line
#define SLEDR__TAB_NEXT_LINE       0x80000092
//**Text:Missing NL character
#define SLEDR__MISSING_NL          0x80000093
//**Text:No pattern found
#define SLEDR__NO_PATT_FOUND       0x80000094
//**Text:Invalid recompile
#define SLEDR__INV_RECOMPINFO      0x80000095
//**Text:Invalid undo/redo info index
#define SLEDR__INV_UNDO_IDX        0x80000096
//**Text:No block number Nxxx, :xxx
#define SLEDR__NO_BLOCKNR_IN_BL    0x80000097
//**Text:There are no writable block is the file
#define SLEDR__NO_WRITABLE_BLOCK   0x80000098
//**Text:There are no dirty lines
#define SLEDR__NO_DIRTY_LINES      0x80000099
//**Text:Block not preset in paint data, not visible
#define SLEDR__BLOCK_NOT_VIS       0x8000009A
//**Text:No line info given
#define SLEDR__NO_LINE_INFO        0x8000009B
//**Text:Inconsistent cache, seek position and block number not in synchron
#define SLEDR__INCONSIST_CACHE     0x8000009C
//**Text:File couldn't be removed
#define SLEDR__FILEREMOVE_ERR      0x8000009D
//**Text:Not enough block in string
#define SLEDR__NOT_ENOUGH_BL       0x8000009E
//**Text:Input file doesn't exist
#define SLEDR__NO_INPUT_FILE       0x8000009F 
//**Text:Step attribute should not be empty
#define SLEDR__EMPTY_STEPATTR      0x800000A0 
//**Text:Actual steps and step attributes are different
#define SLEDR__DIFFERENT_STEPS     0x800000A1 
//**Text:No more blocks found in the buffer
#define SLEDR__NO_MORE_BLOCK       0x800000A2 
//**Text:No pure text step
#define SLEDR__NO_PURETEXT         0x800000A3 
//**Text:The cursor is at the top-left visible position in the file
#define SLEDR__FILE_TOPLEFT_POS    0x800000A4
//**Text:edit object already contains data
#define SLEDR__EDITOBJ_FULL        0x800000A5
//**Text:editor widget is already detached
#define SLEDR__DETACHED            0x800000A6
//**Text:attach is not possible, call detach first
#define SLEDR__NO_ATTACH_POSSIBLE  0x800000A7
//**Text:widget is working, command not possible
#define SLEDR__WORKING             0x800000A8
//**Text:detach is not possible
#define SLEDR__NO_DETACH_POSSIBLE  0x800000A9
//**Text:No private data
#define SLEDR__NO_PRIVATE_DATA     0x800000AA
//**Text:Setting of NC-mode failed
#define SLEDR__SETTING_NCMODE      0x800000AB
//**Text:Step access is not enabled
#define SLEDR__NO_STEP_ACCESS      0x800000AC
//**Text:Not enough steps in the file
#define SLEDR__NOT_ENOUGH_STEPS    0x800000AD 
//**Text:Couldn't load the icon file
#define SLEDR__COULDNT_LOAD_ICON   0x800000AF
//**Text:No interfacepointer to step logic
#define SLEDR__NO_STEP_LOGIC_INST  0x800000B0
//**Text:Caret is at the end of the block
#define SLEDR__BLOCKEND_POS        0x800000B1   
//**Text:Caret is at the beginning of the block
#define SLEDR__BLOCKBEGIN_POS      0x800000B2
//**Text:Block is not in buffer
#define SLEDR__BLOCKS_NOT_IN_BUFFER 0x800000B3
//**Text:Getting interface pointer of MC-View failed
#define SLEDR__CREATE_MCVIEWINST   0x800000B4
//**Text:No interface pointer of MC-view
#define SLEDR__NO_MCVIEWINST       0x800000B5
//**Text:Invalid channel index
#define SLEDR__INVALID_CHANNEL     0x800000B6
//**Text:Invalid number of channels
#define SLEDR__INVALID_CHANNEL_NR  0x800000B7
//**Text:Invalid channel width
#define SLEDR__INVALID_CHANNEL_WIDTH 0x800000B8
//**Text:Channel not visible
#define SLEDR__CHANNEL_NOT_VIS     0x800000B9
//**Text:A file is already opened in this channel
#define SLEDR__FILE_ALREADY_OPENED_IN_CHANNEL  0x800000BA
//**Text:A file is already visible in this column
#define SLEDR__FILE_ALREADY_VISIBLE_IN_COLUMN  0x800000BB
//**Text:Invalid column index
#define SLEDR__INAVLID_COLUMN			 0x800000BC
//**Text:Step isn`t a waitmark step
#define SLEDR__NOT_WAITMARK_STEP	 0x800000BD
//**Text:The Gui thread is not allowed to change the file
#define SLEDR__WRITE_DENIED        0x800000BE
//**Text:Succeeded, but the function did't do anything
#define SLEDR__OK_NOTHING_DONE     0x800000BF
//**Text:The mouse cursor is not in the edit window
#define SLEDR__MOUSE_NOT_IN_VIEW   0x800000C0
//**Text:The file is already locked for write
#define SLEDR__FILE_LOCKED_FOR_WRITE 0x800000C1
//**Text:The file has been changed outside of the actual editor instance
#define SLEDR__FILE_HAS_BEEN_MODIFIED 0x800000C2
//**Text:The temporary file already exists
#define SLEDR__TEMPFILE_EXISTS     0x800000C3
//**Text:The temporary file couldn't be removed
#define SLEDR__TEMPFILE_REMOVE     0x800000C4
//**Text:The temporary file is not opened
#define SLEDR__TEMPFILE_NOTOPEN    0x800000C5
//**Text:The seek position couldn't be changed in a temporary file
#define SLEDR__TEMPFILE_SEEK       0x800000C6
//**Text:Couldn't read the temporary file
#define SLEDR__TEMPFILE_READ       0x800000C7
//**Text:Couldn't create the temporary file
#define SLEDR__TEMPFILE_CREATE     0x800000C8
//**Text:Couldn't write the temporary file
#define SLEDR__TEMPFILE_WRITE      0x800000C9
//**Text:The segment is not in the memory
#define SLEDR__SEGMENT_NOT_IN_MEM  0x800000CA
//**Text:Index is out of range
#define SLEDR__INVALID_INDEX       0x800000CB 
//**Text:Qt error
#define SLEDR__QT_ERR              0x800000CC
//**Text:N-number overflow while renumbering
#define SLEDR__BLNR_OVERFLOW       0x800000CD
//**Text:Wait, until lodading is finished
#define SLEDR__AWAIT_OPEN          0x800000CE
//**Text:Copy/Cut/Paste is rejected, because of the clipboard size
#define SLEDR__CLIPBOARD_SIZE      0x800000CF
//**Text:Couldn't open the temporary file
#define SLEDR__TEMPFILE_OPEN       0x800000D0
//**Text:Maximal block level reached
#define SLEDR__MAXBLOCKLEVEL_REACHED 0x800000D1
//**Text:The file is empty
#define SLEDR__FILE_EMPTY          0x800000D2
//**Text:The program id is invalid
#define SLEDR__INVALID_PROGRAMID   0x800000D3
//**Text:MCE blocks are inconsistent
#define SLEDR__ERR_INVALID_BLOCKS     0x800000D4
//**Text:Copy, delete or paste program head
#define SLEDR__ERR_PROGRAM_HEAD       0x800000D5
//**Text:Copy, delete or paste program end
#define SLEDR__ERR_PROGRAM_END        0x800000D6
//**Text:MCE block has invalid level depth
#define SLEDR__ERR_BLOCK_IN_BLOCK     0x800000D7
//**Text:There are some contours to rename first
#define SLEDR__ERR_CONTOUR_TO_RENAME  0x800000D8
//**Text:SaveFile() is called for EES file, but there is no exclusive lock set.
#define SLEDR__ERR_TRYING_TO_SAVE_WITHOUT_EXCL_LOCK 0x800000E9

//**ErrEndErrorCodes

/*! 
 *  \macro SLEDR_ERROR(X)
 *
 *  Defines the base for return values of the kc logic.
 */
#define SLEDR_ERROR(X)  (SL_ERR_EDITOR|(X))

#endif // SL_ED_ERROR_H
