#include "aimp_vgmstream_core.h"

AIMP_VGMSTREAM_API void vgmstream_close(VGMSTREAM* vgmstream)
{
	close_vgmstream(vgmstream);
}

AIMP_VGMSTREAM_API VGMSTREAM* vgmstream_open_file(FILE* file, const char* filename)
{
	VGMSTREAM* vgmstream = NULL;
	STREAMFILE* sf = open_stdio_streamfile_by_file(file, filename);
	if (sf)
	{
		vgmstream = init_vgmstream_from_STREAMFILE(sf);
		close_streamfile(sf);
	}
	return vgmstream;
}

AIMP_VGMSTREAM_API int vgmstream_read(sample_t* buf, int32_t sample_count, VGMSTREAM* vgmstream)
{
	return render_vgmstream(buf, sample_count, vgmstream);
}

AIMP_VGMSTREAM_API void vgmstream_seek(VGMSTREAM* vgmstream, int32_t seek_sample)
{
	seek_vgmstream(vgmstream, seek_sample);
}
