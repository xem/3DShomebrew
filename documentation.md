#3DS and ctrulib documentation

WIP.

The following document was made by studying the [doxygen build of ctrulib](http://xem.github.io/3DShomebrew/doxygen) and ctrulib's sourcecode.

##Summary
- ctrulib documentation
  - Variables
  - Memory allocator
  - GPU
  - Networking / Sockets
  - AC
  - AM
  - APT
  - CFGNOR
  - CFGU
  - Audio subsystem
  - Filesystem / IO
  - GSP
  - GX
  - User Input / HID
  - HTTPC
  - Infrared Communication
  - IRRST
  - Microphone / Audio capture
  - mvd
  - NS
  - PM
  - PS
  - PTM
  - GFX
  - Srv
  

##ctrulib documentation

###Variables

In addition to [the standard C/C++ types](http://en.cppreference.com/w/cpp/language/types), ctrulib provides the following short-hand types.<br>
They are all types of integers (no decimal numbers), but of course you can use native floating point numbers (with decimals), booleans (true/false) and chars.

````
Unsigned int types:
u8, u16, u32, s64,
vu8, vu16, vu32, vu64

Signed int types:
s8, s16, s32, s64,
vs8, vs16, vs32, vs64
````

* u means unsigned; the number is strictly positive
* s means signed; the number can be positive or negative
* v means volatile; he number can be changed from outside of your code, such as the 3D effect slider value

non-volatile numbers are optimized during compilation.

The above designations are followed by the amount of bits in memory the variable type uses.
<br>
It is important to note that on a desktop PC, there is no difference between the amount of memory an u8 or an u32 take.
<br>
However, on hardware with limited resources such as a 3DS, this difference does exist, and choosing the proper size variable will save you valuable memory capacity.

ctrulib also defines the following constants and macros:

````
U64_MAX // max u64 value (about 1.8e19)
BIT(n)  // returns the nth bit of a number (TODO: confirm that, and explain how to use it)
````

###Memory allocator

####Functions
````
void * 	linearMemAlign (size_t size, size_t alignment)
void * 	linearAlloc (size_t size)
void * 	linearRealloc (void *mem, size_t size)
void 	  linearFree (void *mem)
u32 	  linearSpaceFree ()

bool 	  Ready ()
void 	  AddBlock (MemBlock *blk)
void 	  DelBlock (MemBlock *b)
void 	  InsertBefore (MemBlock *b, MemBlock *p)
void 	  InsertAfter (MemBlock *b, MemBlock *n)
void 	  CoalesceRight (MemBlock *b)
bool 	  Allocate (MemChunk &chunk, u32 size, int align)
void 	  Deallocate (const MemChunk &chunk)
void 	  Destroy ()
u32 	  GetFreeSpace ()
````

###GPU

####Functions

````
void 	GPU_Init (Handle *gsphandle)
void 	GPUCMD_SetBuffer (u32 *adr, u32 size, u32 offset)
void 	GPUCMD_SetBufferOffset (u32 offset)
void 	GPUCMD_GetBuffer (u32 **adr, u32 *size, u32 *offset)
void 	GPUCMD_AddRawCommands (u32 *cmd, u32 size)
void 	GPUCMD_Run (u32 *gxbuf)
void 	GPUCMD_FlushAndRun (u32 *gxbuf)
void 	GPUCMD_Add (u32 cmd, u32 *param, u32 paramlength)
void 	GPUCMD_AddSingleParam (u32 cmd, u32 param)
void 	GPUCMD_Finalize ()
void 	GPU_Reset (u32 *gxbuf, u32 *gpuBuf, u32 gpuBufSize)
void 	GPU_SetUniform (u32 startreg, u32 *data, u32 numreg)
u32 	f32tof24 (float f)
u32 	computeInvValue (u32 val)
void 	GPU_SetViewport (u32 *depthBuffer, u32 *colorBuffer, u32 x, u32 y, u32 w, u32 h)
void 	GPU_SetScissorTest (GPU_SCISSORMODE mode, u32 x, u32 y, u32 w, u32 h)
void 	GPU_DepthRange (float nearVal, float farVal)
void 	GPU_SetAlphaTest (bool enable, GPU_TESTFUNC function, u8 ref)
void 	GPU_SetStencilTest (bool enable, GPU_TESTFUNC function, u8 ref, u8 mask, u8 replace)
void 	GPU_SetStencilOp (GPU_STENCILOP sfail, GPU_STENCILOP dfail, GPU_STENCILOP pass)
void 	GPU_SetDepthTestAndWriteMask (bool enable, GPU_TESTFUNC function, GPU_WRITEMASK writemask)
void 	GPU_SetAlphaBlending (GPU_BLENDEQUATION colorEquation, GPU_BLENDEQUATION alphaEquation, GPU_BLENDFACTOR colorSrc, GPU_BLENDFACTOR colorDst, GPU_BLENDFACTOR alphaSrc, GPU_BLENDFACTOR alphaDst)
void 	GPU_SetColorLogicOp (GPU_LOGICOP op)
void 	GPU_SetBlendingColor (u8 r, u8 g, u8 b, u8 a)
void 	GPU_SetTextureEnable (GPU_TEXUNIT units)
void 	GPU_SetTexture (GPU_TEXUNIT unit, u32 *data, u16 width, u16 height, u32 param, GPU_TEXCOLOR colorType)
void 	GPU_SetAttributeBuffers (u8 totalAttributes, u32 *baseAddress, u64 attributeFormats, u16 attributeMask, u64 attributePermutation, u8 numBuffers, u32 bufferOffsets[], u64 bufferPermutations[], u8 bufferNumAttributes[])
void 	GPU_SetAttributeBuffersAddress (u32 *baseAddress)
void 	GPU_SetFaceCulling (GPU_CULLMODE mode)
void 	GPU_SetTexEnv (u8 id, u16 rgbSources, u16 alphaSources, u16 rgbOperands, u16 alphaOperands, GPU_COMBINEFUNC rgbCombine, GPU_COMBINEFUNC alphaCombine, u32 constantColor)
void 	GPU_DrawArray (GPU_Primitive_t primitive, u32 n)
void 	GPU_DrawElements (GPU_Primitive_t primitive, u32 *indexArray, u32 n)
void 	GPU_FinishDrawing ()

DVLB_s * 	SHDR_ParseSHBIN (u32 *shbinData, u32 shbinSize)
s8 	  SHDR_GetUniformRegister (DVLB_s *dvlb, const char *name, u8 programID)
void 	DVLP_SendCode (DVLP_s *dvlp)
void 	DVLP_SendOpDesc (DVLP_s *dvlp)
void 	DVLE_SendOutmap (DVLE_s *dvle)
void 	DVLE_SendConstants (DVLE_s *dvle)
void 	SHDR_UseProgram (DVLB_s *dvlb, u8 id)
void 	SHDR_FreeDVLB (DVLB_s *dvlb)
````

###Networking/Sockets

####Functions

````
int 	    accept (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
int 	    bind (int sockfd, const struct sockaddr *addr, socklen_t addrlen)
int 	    closesocket (int sockfd)
s32 	    _net_convert_error (s32 sock_retval)
int 	    SOC_GetErrno (void)
int 	    connect (int sockfd, const struct sockaddr *addr, socklen_t addrlen)
int 	    fcntl (int fd, int cmd,...)
struct hostent * 	gethostbyname (const char *name)
long 	    gethostid (void)
int 	    getpeername (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
int 	    getsockname (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
int 	    getsockopt (int sockfd, int level, int optname, void *optval, socklen_t *optlen)
in_addr_t inet_addr (const char *cp)
int 	    inet_aton (const char *cp, struct in_addr *inp)
char * 	  inet_ntoa (struct in_addr in)
Result 	  SOC_Initialize (u32 *context_addr, u32 context_size)
Result 	  SOC_Shutdown (void)
int 	    ioctl (int fd, int request,...)
int 	    listen (int sockfd, int max_connections)
int 	    poll (struct pollfd *fds, nfds_t nfsd, int timeout)
ssize_t 	recv (int sockfd, void *buf, size_t len, int flags)
ssize_t 	socuipc_cmd7 (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
ssize_t 	socuipc_cmd8 (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
ssize_t 	recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
int 	    select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
ssize_t 	send (int sockfd, const void *buf, size_t len, int flags)
ssize_t 	socuipc_cmd9 (int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
ssize_t 	socuipc_cmda (int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
ssize_t 	sendto (int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
int 	    setsockopt (int sockfd, int level, int optname, const void *optval, socklen_t optlen)
int 	    shutdown (int sockfd, int shutdown_type)
int 	    sockatmark (int sockfd)
int 	    socket (int domain, int type, int protocol)
````

####Macros / constants

````
NET_UNKNOWN_ERROR_OFFSET = -10000
MAX_HOSTENT_RESULTS = 16
````

###AC

####Functions
````
Result 	acInit ()
Result 	acExit ()
Result 	ACU_CreateDefaultConfig (Handle *servhandle, u32 *ptr)
Result 	ACU_cmd26 (Handle *servhandle, u32 *ptr, u8 val)
Result 	ACU_GetWifiStatus (Handle *servhandle, u32 *out)
Result 	ACU_WaitInternetConnection ()
````

###AM

#### Functions

````
Result 	amInit ()
Result 	amExit ()
Result 	AM_GetTitleCount (u8 mediatype, u32 *count)
Result 	AM_GetTitleList (u8 mediatype, u32 count, void *buffer)
Result 	AM_GetDeviceId (u32 *deviceid)
Result 	AM_StartCiaInstall (u8 mediatype, Handle *ciahandle)
Result 	AM_StartDlpChildCiaInstall (Handle *ciahandle)
Result 	AM_CancelCIAInstall (Handle *ciahandle)
Result 	AM_FinishCiaInstall (u8 mediatype, Handle *ciahandle)
Result 	AM_DeleteTitle (u8 mediatype, u64 titleid)
Result 	AM_DeleteAppTitle (u8 mediatype, u64 titleid)
Result 	AM_InstallFIRM (u8 mediatype, u64 titleid)
````

###APT

####Functions

````
void 	    aptInitCaptureInfo (u32 *ns_capinfo)
void 	    aptWaitStatusEvent ()
void 	    aptAppletUtility_Exit_RetToApp ()
NS_APPID 	aptGetMenuAppID ()
void 	    aptReturnToMenu ()
void 	    aptAppletStarted ()
void 	    aptAppletClosed ()
void 	    aptEventHandler (u32 arg)
Result 	  aptInit (void)
````

####Macros
````
APT_HANDLER_STACKSIZE = 0x1000
````

###CFGNOR

####Functions
````
Result 	CFGNOR_Initialize (u8 value)
Result 	CFGNOR_Shutdown ()
Result 	CFGNOR_ReadData (u32 offset, u32 *buf, u32 size)
Result 	CFGNOR_WriteData (u32 offset, u32 *buf, u32 size)
Result 	CFGNOR_DumpFlash (u32 *buf, u32 size)
Result 	CFGNOR_WriteFlash (u32 *buf, u32 size)
````

###CFGU

####Functions
````
Result 	initCfgu ()
Result 	exitCfgu ()
Result 	CFGU_GetRegionCanadaUSA (u8 *value)
Result 	CFGU_GetSystemModel (u8 *model)
Result 	CFGU_GetModelNintendo2DS (u8 *value)
Result 	CFGU_GetCountryCodeString (u16 code, u16 *string)
Result 	CFGU_GetCountryCodeID (u16 string, u16 *code)
````

###Audio subsystem

####Functions

````
Result 	CSND_cmd1 (Handle *mutexhandle, Handle *sharedmemhandle, u32 sharedmem_size, u32 off0, u32 off1, u32 off2, u32 off3)
Result 	CSND_cmd2 ()
Result 	CSND_cmd5 (u32 *bitmask)
Result 	CSND_initialize (u32 *sharedMem)
Result 	CSND_shutdown ()
Result 	CSND_cmd3 (u32 offset)
void 	  CSND_writesharedmem_cmdtype0 (u16 cmdid, u8 *cmdparams)
Result 	CSND_processtype0cmds ()
u32 	  CSND_convertsamplerate (u32 samplerate)
void 	  CSND_sharedmemtype0_cmd0 (u32 channel, u32 value)
void 	  CSND_setchannel_playbackstate (u32 channel, u32 value)
void 	  CSND_sharedmemtype0_cmd3 (u32 channel, u32 physaddr, u32 size)
void 	  CSND_sharedmemtype0_cmd9 (u32 channel, u16 value)
void 	  CSND_sharedmemtype0_cmd8 (u32 channel, u32 samplerate)
void 	  CSND_sharedmemtype0_cmde (u32 channel, u32 looping, u32 encoding, u32 samplerate, u32 unk0, u32 unk1, u32 physaddr0, u32 physaddr1, u32 totalbytesize)
Result 	CSND_sharedmemtype0_cmdupdatestate (int waitdone)
Result 	CSND_playsound (u32 channel, u32 looping, u32 encoding, u32 samplerate, u32 *vaddr0, u32 *vaddr1, u32 totalbytesize, u32 unk0, u32 unk1)
Result 	CSND_getchannelstate (u32 entryindex, u32 *out)
Result 	CSND_getchannelstate_isplaying (u32 entryindex, u8 *status)
````

###Filesystem / IO

####Functions

````
Handle 	__get_handle_from_list (char *name)
Result 	fsInit (void)
Result 	fsExit (void)
Result 	FSUSER_Initialize (Handle *handle)
Result 	FSUSER_OpenFile (Handle *handle, Handle *out, FS_archive archive, FS_path fileLowPath, u32 openFlags, u32 attributes)
Result 	FSUSER_OpenFileDirectly (Handle *handle, Handle *out, FS_archive archive, FS_path fileLowPath, u32 openFlags, u32 attributes)
Result 	FSUSER_DeleteFile (Handle *handle, FS_archive archive, FS_path fileLowPath)
Result 	FSUSER_RenameFile (Handle *handle, FS_archive srcArchive, FS_path srcFileLowPath, FS_archive destArchive, FS_path destFileLowPath)
Result 	FSUSER_DeleteDirectory (Handle *handle, FS_archive archive, FS_path dirLowPath)
Result 	FSUSER_DeleteDirectoryRecursively (void)
Result 	FSUSER_CreateFile (void)
Result 	FSUSER_CreateDirectory (Handle *handle, FS_archive archive, FS_path dirLowPath)
Result 	FSUSER_RenameDirectory (Handle *handle, FS_archive srcArchive, FS_path srcDirLowPath, FS_archive destArchive, FS_path destDirLowPath)
Result 	FSUSER_OpenDirectory (Handle *handle, Handle *out, FS_archive archive, FS_path dirLowPath)
Result 	FSUSER_OpenArchive (Handle *handle, FS_archive *archive)
Result 	FSUSER_CloseArchive (Handle *handle, FS_archive *archive)
Result 	FSUSER_GetSdmcArchiveResource (Handle *handle, u32 *sectorSize, u32 *clusterSize, u32 *numClusters, u32 *freeClusters)
Result 	FSUSER_IsSdmcDetected (Handle *handle, u32 *detected)
Result 	FSUSER_IsSdmcWritable (Handle *handle, u32 *writable)
Result 	FSFILE_Close (Handle handle)
Result 	FSFILE_Read (Handle handle, u32 *bytesRead, u64 offset, void *buffer, u32 size)
Result 	FSFILE_Write (Handle handle, u32 *bytesWritten, u64 offset, const void *buffer, u32 size, u32 flushFlags)
Result 	FSFILE_GetSize (Handle handle, u64 *size)
Result 	FSFILE_SetSize (Handle handle, u64 size)
Result 	FSFILE_GetAttributes (Handle handle, u32 *attributes)
Result 	FSFILE_SetAttributes (Handle handle, u32 attributes)
Result 	FSFILE_Flush (Handle handle)
Result 	FSDIR_Read (Handle handle, u32 *entriesRead, u32 entryCount, FS_dirent *buffer)
Result 	FSDIR_Close (Handle handle)
````

####Macros / constants

File opening

````
FS_OPEN_READ = 1    // open a file to read it
FS_OPEN_WRITE = 2   // open a file to write in it
FS_OPEN_CREATE = 4  // create a file if it doesn't exist, and open it
````
(used in FSUSER_OpenFile() and FSUSER_OpenFileDirectly())

File creation
````
FS_ATTRIBUTE_NONE = 0x00000000      // create a file without special attributes
FS_ATTRIBUTE_READONLY = 0x00000001  // create an readonly file
FS_ATTRIBUTE_ARCHIVE = 0x00000100   // create an archive
FS_ATTRIBUTE_HIDDEN = 0x00010000    // create a hidden file
FS_ATTRIBUTE_DIRECTORY = 0x01000000 // create a directory
````
(used in FSUSER_OpenFile() and FSUSER_OpenFileDirectly())

File writing parameters

When writing to the filesystem, usually the operating system will wait with actually writing the file data to the storage medium until a certain amount of data has been 'written'. You can specify that you want to write+flush, or just write. 
Meaning; you can let the OS decide when to do the writing, or you can force the data to be 
written to the file immediately. In most cases, you will not need to force flushing.
````
FS_WRITE_NOFLUSH = 0x00000000 // write without flush
FS_WRITE_FLUSH = 0x00010001   // write with flush
````

(used in FSFILE_Write())

###GSP

(screen capture?)

####Functions

````
Result 	gspInit ()
void 	  gspExit ()
Result 	gspInitEventHandler (Handle _gspEvent, vu8 *_gspSharedMem, u8 gspThreadId)
void 	  gspExitEventHandler ()
void 	  gspWaitForEvent (GSP_Event id, bool nextEvent)
Result 	GSPGPU_WriteHWRegs (Handle *handle, u32 regAddr, u32 *data, u8 size)
Result 	GSPGPU_WriteHWRegsWithMask (Handle *handle, u32 regAddr, u32 *data, u8 datasize, u32 *maskdata, u8 masksize)
Result 	GSPGPU_ReadHWRegs (Handle *handle, u32 regAddr, u32 *data, u8 size)
Result 	GSPGPU_SetBufferSwap (Handle *handle, u32 screenid, GSP_FramebufferInfo *framebufinfo)
Result 	GSPGPU_FlushDataCache (Handle *handle, u8 *adr, u32 size)
Result 	GSPGPU_InvalidateDataCache (Handle *handle, u8 *adr, u32 size)
Result 	GSPGPU_SetLcdForceBlack (Handle *handle, u8 flags)
Result 	GSPGPU_TriggerCmdReqQueue (Handle *handle)
Result 	GSPGPU_RegisterInterruptRelayQueue (Handle *handle, Handle eventHandle, u32 flags, Handle *outMemHandle, u8 *threadID)
Result 	GSPGPU_UnregisterInterruptRelayQueue (Handle *handle)
Result 	GSPGPU_AcquireRight (Handle *handle, u8 flags)
Result 	GSPGPU_ReleaseRight (Handle *handle)
Result 	GSPGPU_ImportDisplayCaptureInfo (Handle *handle, GSP_CaptureInfo *captureinfo)
Result 	GSPGPU_SaveVramSysArea (Handle *handle)
Result 	GSPGPU_RestoreVramSysArea (Handle *handle)
Result 	GSPGPU_SubmitGxCommand (u32 *sharedGspCmdBuf, u32 gxCommand[0x8], Handle *handle)
````

####Macros / constants

````
GSP_EVENT_STACK_SIZE = 0x1000
````

###GX

####Functions

````
Result 	GX_RequestDma (u32 *gxbuf, u32 *src, u32 *dst, u32 length)
Result 	GX_SetCommandList_Last (u32 *gxbuf, u32 *buf0a, u32 buf0s, u8 flags)
Result 	GX_SetMemoryFill (u32 *gxbuf, u32 *buf0a, u32 buf0v, u32 *buf0e, u16 width0, u32 *buf1a, u32 buf1v, u32 *buf1e, u16 width1)
Result 	GX_SetDisplayTransfer (u32 *gxbuf, u32 *inadr, u32 indim, u32 *outadr, u32 outdim, u32 flags)
Result 	GX_SetTextureCopy (u32 *gxbuf, u32 *inadr, u32 indim, u32 *outadr, u32 outdim, u32 size, u32 flags)
Result 	GX_SetCommandList_First (u32 *gxbuf, u32 *buf0a, u32 buf0s, u32 *buf1a, u32 buf1s, u32 *buf2a, u32 buf2s)
````

###User Input/HID

####Functions

````
Result 	hidInit (u32 *sharedMem)
void 	  hidExit ()
void 	  hidWaitForEvent (HID_Event id, bool nextEvent)
u32 	  hidCheckSectionUpdateTime (vu32 *sharedmem_section, u32 id)
void 	  hidScanInput ()
u32 	  hidKeysHeld ()
u32 	  hidKeysDown ()
u32 	  hidKeysUp ()
void 	  hidTouchRead (touchPosition *pos)
void 	  hidCircleRead (circlePosition *pos)
void 	  hidAccelRead (accelVector *vector)
void 	  hidGyroRead (angularRate *rate)
Result 	HIDUSER_GetHandles (Handle *outMemHandle, Handle *eventpad0, Handle *eventpad1, Handle *eventaccel, Handle *eventgyro, Handle *eventdebugpad)
Result 	HIDUSER_EnableAccelerometer ()
Result 	HIDUSER_DisableAccelerometer ()
Result 	HIDUSER_EnableGyroscope ()
Result 	HIDUSER_DisableGyroscope ()
````

###HTTPC

####Functions

````
Result 	httpcInit ()
void 	  httpcExit ()
Result 	httpcOpenContext (httpcContext *context, char *url, u32 use_defaultproxy)
Result 	httpcCloseContext (httpcContext *context)
Result 	httpcAddRequestHeaderField (httpcContext *context, char *name, char *value)
Result 	httpcBeginRequest (httpcContext *context)
Result 	httpcReceiveData (httpcContext *context, u8 *buffer, u32 size)
Result 	httpcGetRequestState (httpcContext *context, httpcReqStatus *out)
Result 	httpcGetDownloadSizeState (httpcContext *context, u32 *downloadedsize, u32 *contentsize)
Result 	httpcGetResponseStatusCode (httpcContext *context, u32 *out, u64 delay)
Result 	httpcDownloadData (httpcContext *context, u8 *buffer, u32 size, u32 *downloadedsize)
Result 	HTTPC_Initialize (Handle handle)
Result 	HTTPC_CreateContext (Handle handle, char *url, Handle *contextHandle)
Result 	HTTPC_InitializeConnectionSession (Handle handle, Handle contextHandle)
Result 	HTTPC_SetProxyDefault (Handle handle, Handle contextHandle)
Result 	HTTPC_CloseContext (Handle handle, Handle contextHandle)
Result 	HTTPC_AddRequestHeaderField (Handle handle, Handle contextHandle, char *name, char *value)
Result 	HTTPC_BeginRequest (Handle handle, Handle contextHandle)
Result 	HTTPC_ReceiveData (Handle handle, Handle contextHandle, u8 *buffer, u32 size)
Result 	HTTPC_GetRequestState (Handle handle, Handle contextHandle, httpcReqStatus *out)
Result 	HTTPC_GetDownloadSizeState (Handle handle, Handle contextHandle, u32 *downloadedsize, u32 *contentsize)
Result 	HTTPC_GetResponseStatusCode (Handle handle, Handle contextHandle, u32 *out)
````

###Infrared Communication

####Functions

````
Result 	irucmd_Initialize ()
Result 	irucmd_Shutdown ()
Result 	irucmd_StartSendTransfer (u8 *buf, u32 size)
Result 	irucmd_WaitSendTransfer ()
Result 	irucmd_StartRecvTransfer (u32 size, u8 flag)
Result 	irucmd_WaitRecvTransfer (u32 *transfercount)
Result 	IRU_SetBitRate (u8 value)
Result 	IRU_GetBitRate (u8 *out)
Result 	IRU_SetIRLEDState (u32 value)
Result 	IRU_GetIRLEDRecvState (u32 *out)
Result 	IRU_Initialize (u32 *sharedmem_addr, u32 sharedmem_size)
Result 	IRU_Shutdown ()
Handle 	IRU_GetServHandle ()
Result 	IRU_SendData (u8 *buf, u32 size, u32 wait)
Result 	IRU_RecvData (u8 *buf, u32 size, u8 flag, u32 *transfercount, u32 wait)
````

###IRRST

####Functions

````
Result 	irrstInit (u32 *sharedMem)
void 	  irrstExit ()
void 	  irrstWaitForEvent (bool nextEvent)
u32 	  irrstCheckSectionUpdateTime (vu32 *sharedmem_section, u32 id)
void 	  irrstScanInput ()
u32 	  irrstKeysHeld ()
void 	  irrstCstickRead (circlePosition *pos)
Result 	IRRST_GetHandles (Handle *outMemHandle, Handle *outEventHandle)
Result 	IRRST_Initialize (u32 unk1, u8 unk2)
Result 	IRRST_Shutdown (void)
````

###Microphone/Audio capture

####Functions

````
Result 	MIC_Initialize (u32 *sharedmem, u32 sharedmem_size, u8 control, u8 recording, u8 unk0, u8 unk1, u8 unk2)
Result 	MIC_Shutdown ()
u32 	  MIC_GetSharedMemOffsetValue ()
u32 	  MIC_ReadAudioData (u8 *outbuf, u32 readsize, u32 waitforevent)
Result 	MIC_MapSharedMem (Handle handle, u32 size)
Result 	MIC_UnmapSharedMem ()
Result 	MIC_cmd3_Initialize (u8 unk0, u8 unk1, u32 sharedmem_baseoffset, u32 sharedmem_endoffset, u8 unk2)
Result 	MIC_cmd5 ()
Result 	MIC_GetCNTBit15 (u8 *out)
Result 	MIC_GetEventHandle (Handle *handle)
Result 	MIC_SetControl (u8 value)
Result 	MIC_GetControl (u8 *value)
Result 	MIC_SetRecording (u8 value)
Result 	MIC_IsRecoding (u8 *value)
````

###mvd

####Functions

````
Result  mvdstdSetConfig (mvdstdConfig *config)
void    mvdstdGenerateDefaultConfig (mvdstdConfig *config, u32 input_width, u32 input_height, u32 output_width, u32 output_height, u32 *vaddr_colorconv_indata, u32 *vaddr_outdata0, u32 *vaddr_outdata1_colorconv)
Result 	mvdstdInit (mvdstdMode mode, mvdstdTypeInput input_type, mvdstdTypeOutput output_type, u32 size)
Result 	mvdstdShutdown ()
Result 	mvdstdProcessFrame (mvdstdConfig *config, u32 *h264_vaddr_inframe, u32 h264_inframesize, u32 h264_frameid)
````

###NS

####Functions

````
Result 	nsInit ()
Result 	nsExit ()
Result 	NS_LaunchTitle (u64 titleid, u32 launch_flags, u32 *procid)
Result 	NS_RebootToTitle (u8 mediatype, u64 titleid)
````

###PM

####Functions

````
Result 	pmInit ()
Result 	pmExit ()
Result 	PM_LaunchTitle (u8 mediatype, u64 titleid, u32 launch_flags)
Result 	PM_GetTitleExheaderFlags (u8 mediatype, u64 titleid, u8 *out)
Result 	PM_SetFIRMLaunchParams (u32 size, u8 *in)
Result 	PM_GetFIRMLaunchParams (u32 size, u8 *out)
Result 	PM_LaunchFIRMSetParams (u32 firm_titleid_low, u32 size, u8 *in)
````

### PS

####Functions

````
Result 	psInit ()
Result 	psExit ()
Result 	PS_EncryptDecryptAes (u32 size, u8 *in, u8 *out, u32 aes_algo, u32 key_type, u8 *iv)
Result 	PS_EncryptSignDecryptVerifyAesCcm (u8 *in, u32 in_size, u8 *out, u32 out_size, u32 data_len, u32 mac_data_len, u32 mac_len, u32 aes_algo, u32 key_type, u8 *nonce)
Result 	PS_GetLocalFriendCodeSeed (u64 *seed)
Result 	PS_GetDeviceId (u32 *device_id)
````

###PTM

####Functions

````
Result 	ptmInit ()
Result 	ptmExit ()
Result 	PTMU_GetShellState (Handle *servhandle, u8 *out)
Result 	PTMU_GetBatteryLevel (Handle *servhandle, u8 *out)
Result 	PTMU_GetBatteryChargeState (Handle *servhandle, u8 *out)
Result 	PTMU_GetPedometerState (Handle *servhandle, u8 *out)
Result 	PTMU_GetTotalStepCount (Handle *servhandle, u32 *steps)
````

###GFX

####Functions

````
void 	gfxSet3D (bool enable)
void 	gfxSetFramebufferInfo (gfxScreen_t screen, u8 id)
void 	gfxWriteFramebufferInfo (gfxScreen_t screen)
void 	gfxInit ()
void 	gfxExit ()
u8 * 	gfxGetFramebuffer (gfxScreen_t screen, gfx3dSide_t side, u16 *width, u16 *height)
void 	gfxFlushBuffers ()
void 	gfxSwapBuffers ()
void 	gfxSwapBuffersGpu ()
````

###Srv

####Functions

````
Handle 	__get_handle_from_list (const char *name)
void 	  __destroy_handle_list (void)
Result 	srvInit ()
Result 	srvExit ()
Result 	srvRegisterClient ()
Result 	srvGetServiceHandle (Handle *out, const char *name)
Result 	srvPmInit ()
Result 	srvRegisterProcess (u32 procid, u32 count, void *serviceaccesscontrol)
Result 	srvUnregisterProcess (u32 procid)
````
