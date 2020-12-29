#include  <stdint.h>



#pragma pack(push,1)
typedef struct
{
	//BITMAP FILE HEADER
        u_int16_t bi_Identifier;
	u_int32_t bi_File_Size;
	u_int32_t bi_Reserved;
	u_int32_t bi_Bitmap_Data_Offset;

	//BITMAP INFO HEADER
	u_int32_t bi_Size;
	u_int32_t bi_Width;
	u_int32_t bi_Height;
	u_int16_t bi_planes;
	u_int16_t bi_bit_count;
        u_int32_t bi_compression;
	u_int32_t bi_image_size;
	u_int32_t bi_x_pels_per_meter;
	u_int32_t bi_y_pels_per_meter;	
	u_int32_t bi_clr_used;
	u_int32_t bi_clr_important;

	//BITMAP PIXEL RGB
	BITMAP_PIXEL bi_pixel;
}BITMAP_FILE_INFO_HEADER;

typedef struct
{
	uint8_t bi_B;
	uint8_t bi_G;
	uint8_t bi_R;
	uint8_t bi_reserved;
}BITMAP_PIXEL;
#pragma pack(pop)

