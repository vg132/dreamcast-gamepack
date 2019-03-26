#include <kos.h>
#include "main/gamepack.hpp"

pvr_init_params_t params = {
  /* Enable opaque and translucent polygons with size 16 */
  {PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0,
   PVR_BINSIZE_0},

  /* Vertex buffer size 512K */
        512 * 1024
};

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv)
{
	pvr_init(&params);
	CGamePack gp;
	gp.Start();
	return(0);
}

