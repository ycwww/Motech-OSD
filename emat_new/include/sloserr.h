/*! \file   sloserr.h
 *  \author Harald Amrehn
 *  \date   27.01.2011
 *  \brief  Error codes for operating system api
 *
 *  (C) Copyright Siemens AG 2011
*/

#ifndef SLOS_ERR_H_
#define SLOS_ERR_H_

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x08000000
//**ModuleName: HMI sl operating system api
//**TextFile:
//**TextContext:

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Operation not permitted
#define	SLOS_EPERM		 0x80000001
//**Text:No such file or directory
#define	SLOS_ENOENT		 0x80000002
//**Text:No such process
#define	SLOS_ESRCH		 0x80000003
//**Text:Interrupted system call
#define	SLOS_EINTR		 0x80000004
//**Text:I/O error
#define	SLOS_EIO		   0x80000005
//**Text:No such device or address
#define	SLOS_ENXIO		 0x80000006
//**Text:Argument list too long
#define	SLOS_E2BIG		 0x80000007
//**Text:Exec format error
#define	SLOS_ENOEXEC	 0x80000008
//**Text:Bad file number
#define	SLOS_EBADF		 0x80000009
//**Text:No child processes
#define	SLOS_ECHILD		 0x8000000A
//**Text:Try again
#define	SLOS_EAGAIN		 0x8000000B
//**Text:Out of memory
#define	SLOS_ENOMEM		 0x8000000C
//**Text:Permission denied
#define	SLOS_EACCES		 0x8000000D
//**Text:Bad address
#define	SLOS_EFAULT		 0x8000000E
//**Text:Block device required
#define	SLOS_ENOTBLK	 0x8000000F
//**Text:Device or resource busy
#define	SLOS_EBUSY		 0x80000010
//**Text:File exists
#define	SLOS_EEXIST		 0x80000011
//**Text:Cross-device link
#define	SLOS_EXDEV		 0x80000012
//**Text:No such device
#define	SLOS_ENODEV		 0x80000013
//**Text:Not a directory
#define	SLOS_ENOTDIR	 0x80000014
//**Text:Is a directory
#define	SLOS_EISDIR		 0x80000015
//**Text:Invalid argument
#define	SLOS_EINVAL		 0x80000016
//**Text:File table overflow
#define	SLOS_ENFILE		 0x80000017
//**Text:Too many open files
#define	SLOS_EMFILE		 0x80000018
//**Text:Not a typewriter
#define	SLOS_ENOTTY		 0x80000019
//**Text:Text file busy
#define	SLOS_ETXTBSY	 0x8000001A
//**Text:File too large
#define	SLOS_EFBIG		 0x8000001B
//**Text:No space left on device
#define	SLOS_ENOSPC		 0x8000001C
//**Text:Illegal seek
#define	SLOS_ESPIPE		 0x8000001D
//**Text:Read-only file system
#define	SLOS_EROFS		 0x8000001E
//**Text:Too many links
#define	SLOS_EMLINK		 0x8000001F
//**Text:Broken pipe
#define	SLOS_EPIPE		 0x80000020
//**Text:Math argument out of domain of func
#define	SLOS_EDOM		   0x80000021
//**Text:Math result not representable
#define	SLOS_ERANGE		 0x80000022
//**Text:Resource deadlock would occur
#define	SLOS_EDEADLK	 0x80000023
//**Text:File name too long
#define	SLOS_ENAMETOOLONG	0x80000024
//**Text:No record locks available
#define	SLOS_ENOLCK		 0x80000025
//**Text:Function not implemented
#define	SLOS_ENOSYS		 0x80000026
//**Text:Directory not empty
#define	SLOS_ENOTEMPTY	0x80000027
//**Text:Too many symbolic links encountered
#define	SLOS_ELOOP		 0x80000028
//**Text:No message of desired type
#define	SLOS_ENOMSG		 0x8000002A
//**Text:Identifier removed
#define	SLOS_EIDRM		 0x8000002B
//**Text:Channel number out of range
#define	SLOS_ECHRNG		 0x8000002C
//**Text:Level 2 not synchronized
#define	SLOS_EL2NSYNC	 0x8000002D
//**Text:Level 3 halted
#define	SLOS_EL3HLT		 0x8000002E
//**Text:Level 3 reset
#define	SLOS_EL3RST		 0x8000002F
//**Text:Link number out of range
#define	SLOS_ELNRNG		 0x80000030
//**Text:Protocol driver not attached
#define	SLOS_EUNATCH	 0x80000031
//**Text:No CSI structure available
#define	SLOS_ENOCSI		 0x80000032
//**Text:Level 2 halted
#define	SLOS_EL2HLT		 0x80000033
//**Text:Invalid exchange
#define	SLOS_EBADE		 0x80000034
//**Text:Invalid request descriptor
#define	SLOS_EBADR		 0x80000035
//**Text:Exchange full
#define	SLOS_EXFULL		 0x80000036
//**Text:No anode
#define	SLOS_ENOANO		 0x80000037
//**Text:Invalid request code
#define	SLOS_EBADRQC	 0x80000038
//**Text:Invalid slot
#define	SLOS_EBADSLT	 0x80000039
//**Text:Bad font file format
#define	SLOS_EBFONT		 0x8000003B
//**Text:Device not a stream
#define	SLOS_ENOSTR		 0x8000003C
//**Text:No data available
#define	SLOS_ENODATA	 0x8000003D
//**Text:Timer expired
#define	SLOS_ETIME		 0x8000003E
//**Text:Out of streams resources
#define	SLOS_ENOSR		 0x8000003F
//**Text:Machine is not on the network
#define	SLOS_ENONET		 0x80000040
//**Text:Package not installed
#define	SLOS_ENOPKG		 0x80000041
//**Text:Object is remote
#define	SLOS_EREMOTE	 0x80000042
//**Text:Link has been severed
#define	SLOS_ENOLINK	 0x80000043
//**Text:Advertise error
#define	SLOS_EADV		   0x80000044
//**Text:Srmount error
#define	SLOS_ESRMNT		 0x80000045
//**Text:Communication error on send
#define	SLOS_ECOMM		 0x80000046
//**Text:Protocol error
#define	SLOS_EPROTO		 0x80000047
//**Text:Multihop attempted
#define	SLOS_EMULTIHOP 0x80000048
//**Text:RFS specific error
#define	SLOS_EDOTDOT	 0x80000049
//**Text:Not a data message
#define	SLOS_EBADMSG	 0x8000004A
//**Text:Value too large for defined data type
#define	SLOS_EOVERFLOW 0x8000004B
//**Text:Name not unique on network
#define	SLOS_ENOTUNIQ	 0x8000004C
//**Text:File descriptor in bad state
#define	SLOS_EBADFD		 0x8000004D
//**Text:Remote address changed
#define	SLOS_EREMCHG	 0x8000004E
//**Text:Can not access a needed shared library
#define	SLOS_ELIBACC	 0x8000004F
//**Text:Accessing a corrupted shared library
#define	SLOS_ELIBBAD	 0x80000050
//**Text:.lib section in a.out corrupted
#define	SLOS_ELIBSCN	 0x80000051
//**Text:Attempting to link in too many shared libraries
#define	SLOS_ELIBMAX	 0x80000052	/*  */
//**Text:Cannot exec a shared library directly
#define	SLOS_ELIBEXEC	 0x80000053
//**Text:Illegal byte sequence
#define	SLOS_EILSEQ		 0x80000054
//**Text:Interrupted system call should be restarted
#define	SLOS_ERESTART	 0x80000055
//**Text:Streams pipe error
#define	SLOS_ESTRPIPE	 0x80000056
//**Text:Too many users
#define	SLOS_EUSERS		 0x80000057
//**Text:Socket operation on non-socket
#define	SLOS_ENOTSOCK	 0x80000058
//**Text:Destination address required
#define	SLOS_EDESTADDRREQ	0x80000059
//**Text:Message too long
#define	SLOS_EMSGSIZE	 0x8000005A
//**Text:Protocol wrong type for socket
#define	SLOS_EPROTOTYPE	0x8000005B
//**Text:Protocol not available
#define	SLOS_ENOPROTOOPT 0x8000005C
//**Text:Protocol not supported
#define	SLOS_EPROTONOSUPPORT 0x8000005D
//**Text:Socket type not supported
#define	SLOS_ESOCKTNOSUPPORT 0x8000005E
//**Text:Operation not supported on transport endpoint
#define	SLOS_EOPNOTSUPP	0x8000005F
//**Text:Protocol family not supported
#define	SLOS_EPFNOSUPPORT 0x80000060
//**Text:Address family not supported by protocol
#define	SLOS_EAFNOSUPPORT 0x80000061
//**Text:Address already in use
#define	SLOS_EADDRINUSE	0x80000062
//**Text:Cannot assign requested address
#define	SLOS_EADDRNOTAVAIL 0x80000063
//**Text:Network is down
#define	SLOS_ENETDOWN	 0x80000064
//**Text:Network is unreachable
#define	SLOS_ENETUNREACH 0x80000065
//**Text:Network dropped connection because of reset
#define	SLOS_ENETRESET 0x80000066
//**Text:Software caused connection abort
#define	SLOS_ECONNABORTED	0x80000067
//**Text:Connection reset by peer
#define	SLOS_ECONNRESET	0x80000068
//**Text:No buffer space available
#define	SLOS_ENOBUFS	 0x80000069
//**Text:Transport endpoint is already connected
#define	SLOS_EISCONN	 0x8000006A
//**Text:Transport endpoint is not connected
#define	SLOS_ENOTCONN	 0x8000006B
//**Text:Cannot send after transport endpoint shutdown
#define	SLOS_ESHUTDOWN 0x8000006C
//**Text:Too many references: cannot splice
#define	SLOS_ETOOMANYREFS	0x8000006D
//**Text:Connection timed out
#define	SLOS_ETIMEDOUT 0x8000006E
//**Text:Connection refused
#define	SLOS_ECONNREFUSED	0x8000006F
//**Text:Host is down
#define	SLOS_EHOSTDOWN 0x80000070
//**Text:No route to host
#define	SLOS_EHOSTUNREACH	0x80000071
//**Text:Operation already in progress
#define	SLOS_EALREADY	 0x80000072
//**Text:Operation now in progress
#define	SLOS_EINPROGRESS 0x80000073
//**Text:Stale NFS file handle
#define	SLOS_ESTALE		 0x80000074
//**Text:Structure needs cleaning
#define	SLOS_EUCLEAN	 0x80000075
//**Text:Not a named type file
#define	SLOS_ENOTNAM	 0x80000076
//**Text:No semaphores available
#define	SLOS_ENAVAIL	 0x80000077
//**Text:Is a named type file
#define	SLOS_EISNAM		 0x80000078
//**Text:Remote I/O error
#define	SLOS_EREMOTEIO 0x80000079
//**Text:Quota exceeded
#define	SLOS_EDQUOT		 0x8000007A
//**Text:No medium found
#define	SLOS_ENOMEDIUM 0x8000007B
//**Text:Wrong medium type
#define	SLOS_EMEDIUMTYPE 0x8000007C
//**Text:Operation Canceled
#define	SLOS_ECANCELED 0x8000007D
//**Text:Required key not available
#define	SLOS_ENOKEY		 0x8000007E
//**Text:Key has expired
#define	SLOS_EKEYEXPIRED 0x8000007F
//**Text:Key has been revoked
#define	SLOS_EKEYREVOKED 0x80000080
//**Text:Key was rejected by service
#define	SLOS_EKEYREJECTED 0x80000081
//**Text:Owner died
#define	SLOS_EOWNERDEAD	0x80000082
//**Text:State not recoverable
#define	SLOS_ENOTRECOVERABLE 0x80000083
//**ErrEndErrorCodes

#endif // SLOS_ERR_H_
