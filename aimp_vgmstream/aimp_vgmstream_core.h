#pragma once
#include <vgmstream.h>

#define AIMP_VGMSTREAM_API __declspec(dllexport)

#ifdef __cplusplus
extern "C"
{
#endif

	// Special bridge to C code

	AIMP_VGMSTREAM_API void vgmstream_close(VGMSTREAM* vgmstream);
	AIMP_VGMSTREAM_API VGMSTREAM* vgmstream_open_file(FILE* file, const char* filename);
	AIMP_VGMSTREAM_API int vgmstream_read(sample_t* buf, int32_t sample_count, VGMSTREAM* vgmstream);
	AIMP_VGMSTREAM_API void vgmstream_seek(VGMSTREAM* vgmstream, int32_t seek_sample);

#ifdef __cplusplus
}
#endif