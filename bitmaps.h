// 'block', 12x12px
const unsigned char epd_bitmap_block [] PROGMEM = {
	0xfe, 0x9b, 0xad, 0xed, 0x7f, 0x7d, 0xe7, 0xe3, 0x37, 0x1d, 0x7b, 0xfe, 0x07, 0x0f, 0x09, 0x0b, 
	0x0e, 0x0c, 0x0e, 0x0f, 0x0b, 0x09, 0x0f, 0x07
};
// 'block1', 12x12px
const unsigned char epd_bitmap_block1 [] PROGMEM = {
	0xfe, 0x03, 0x99, 0xc9, 0x01, 0x65, 0x2d, 0x0d, 0x61, 0x61, 0x03, 0xfe, 0x07, 0x0c, 0x09, 0x09, 
	0x08, 0x08, 0x0b, 0x0b, 0x09, 0x08, 0x0c, 0x07
};
// 'block2', 12x12px
const unsigned char epd_bitmap_block2 [] PROGMEM = {
	0xfe, 0x63, 0xc3, 0x7f, 0x67, 0xc1, 0xc1, 0x49, 0x7f, 0x41, 0xff, 0xfe, 0x07, 0x0e, 0x08, 0x08, 
	0x08, 0x0f, 0x08, 0x08, 0x0c, 0x0c, 0x0f, 0x07
};
// 'block4', 12x12px
const unsigned char epd_bitmap_block4 [] PROGMEM = {
	0xfe, 0xff, 0xff, 0x67, 0x03, 0xc0, 0x87, 0x2f, 0x7f, 0xff, 0xff, 0xfe, 0x07, 0x0f, 0x0f, 0x00, 
	0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x07, 0x0f, 0x07
};
// 'block3', 12x12px
const unsigned char epd_bitmap_block3 [] PROGMEM = {
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xf3, 0xf3, 0xff, 0xfe, 0x07, 0x0f, 0x0f, 0x0f, 
	0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07
};
// 'digman', 12x12px
const unsigned char epd_bitmap_digman [] PROGMEM = {
	0x00, 0x00, 0x1c, 0x22, 0x5d, 0xc1, 0xc1, 0x5d, 0x22, 0xdc, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x02, 
	0x0f, 0x07, 0x07, 0x0f, 0x03, 0x01, 0x00, 0x00
};
// 'time', 12x12px
const unsigned char epd_bitmap_time [] PROGMEM = {
	0x00, 0xf8, 0x04, 0x02, 0x02, 0xc2, 0x22, 0x12, 0x02, 0x04, 0xf8, 0x00, 0x00, 0x01, 0x02, 0x04, 
	0x04, 0x05, 0x04, 0x04, 0x04, 0x02, 0x01, 0x00
};
// 'speed', 12x12px
const unsigned char epd_bitmap_speed [] PROGMEM = {
	0x20, 0xa8, 0xa8, 0xa8, 0x88, 0x00, 0x10, 0xb8, 0xfc, 0xf6, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00
};
// 'speed1', 12x12px
const unsigned char epd_bitmap_speed1 [] PROGMEM = {
	0x00, 0x20, 0xa8, 0xa8, 0x88, 0x00, 0x10, 0xb8, 0xec, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
};
// 'coin1', 12x12px
const unsigned char epd_bitmap_coin1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0xf8, 0x04, 0xf4, 0xf4, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00
};
// 'coin100', 12x12px
const unsigned char epd_bitmap_coin100 [] PROGMEM = {
	0x00, 0x30, 0x48, 0x9c, 0x5c, 0x3c, 0x3c, 0x54, 0x9c, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00
};
// 'coin10', 12x12px
const unsigned char epd_bitmap_coin10 [] PROGMEM = {
	0x00, 0x00, 0xf8, 0x04, 0x0a, 0xf2, 0xf2, 0x0a, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 
	0x05, 0x04, 0x04, 0x05, 0x02, 0x01, 0x00, 0x00
};
// 'spider', 12x12px
const unsigned char epd_bitmap_spider [] PROGMEM = {
	0x00, 0xc8, 0x50, 0xe2, 0x14, 0xf8, 0xf8, 0x14, 0xe2, 0x50, 0xc8, 0x00, 0x00, 0x04, 0x02, 0x01, 
	0x02, 0x07, 0x07, 0x02, 0x01, 0x02, 0x04, 0x00
};
// 'spiderV2', 12x12px
const unsigned char epd_bitmap_spiderV2 [] PROGMEM = {
	0x00, 0x00, 0x88, 0x50, 0xf4, 0x58, 0x58, 0xf4, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 
	0x01, 0x03, 0x03, 0x01, 0x02, 0x00, 0x00, 0x00
};
// 'coin10 (2)', 12x12px
const unsigned char epd_bitmap_coin10_v2 [] PROGMEM = {
	0x00, 0x00, 0xf8, 0x04, 0xfa, 0xfa, 0xca, 0xfa, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 
	0x05, 0x05, 0x05, 0x05, 0x02, 0x01, 0x00, 0x00
};
// 'coin10 (3)', 12x12px
const unsigned char epd_bitmap_coin10_v3 [] PROGMEM = {
	0x00, 0x00, 0x00, 0xf8, 0xf4, 0x0a, 0x0a, 0xf4, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x02, 0x05, 0x05, 0x02, 0x01, 0x00, 0x00, 0x00
};
// 'coin1 (1)', 12x12px
const unsigned char epd_bitmap_coin1_v2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0xf0, 0x08, 0x68, 0x68, 0x08, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00
};
// 'coin1 (2)', 12x12px
const unsigned char epd_bitmap_coin1_v3 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xe8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

// NEW //
// 'coin10 (3)', 12x12px
const unsigned char epd_bitmap_coin10__3_ [] PROGMEM = {
	0x00, 0x00, 0x00, 0xf8, 0xf4, 0x0a, 0x0a, 0xf4, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x02, 0x05, 0x05, 0x02, 0x01, 0x00, 0x00, 0x00
};
// 'coin1 (1)', 12x12px
const unsigned char epd_bitmap_coin1__1_ [] PROGMEM = {
	0x00, 0x00, 0x00, 0xf0, 0x08, 0x68, 0x68, 0x08, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00
};

// 'digmanV2', 12x12px
const unsigned char epd_bitmap_digmanV2 [] PROGMEM = {
	0x00, 0x00, 0x1c, 0x22, 0xa9, 0xe1, 0xe1, 0xa9, 0x22, 0xdc, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x03, 
	0x0f, 0x07, 0x07, 0x0f, 0x03, 0x01, 0x00, 0x00
};
// 'mute', 12x12px
const unsigned char epd_bitmap_mute [] PROGMEM = {
	0x00, 0x08, 0xf0, 0xf0, 0x08, 0x00, 0xfc, 0x04, 0x08, 0x90, 0xf0, 0x00, 0x00, 0x01, 0x00, 0x00, 
	0x01, 0x00, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00
};
// 'sound', 12x12px
const unsigned char epd_bitmap_sound [] PROGMEM = {
	0x00, 0xf8, 0x04, 0xf0, 0x08, 0x00, 0xfc, 0x04, 0x08, 0x90, 0xf0, 0x00, 0x00, 0x01, 0x02, 0x00, 
	0x01, 0x00, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00
};
// 'fullHeart', 12x12px
const unsigned char epd_bitmap_fullHeart [] PROGMEM = {
	0x00, 0x38, 0x7c, 0xfc, 0xfc, 0xf8, 0xf8, 0xfc, 0xfc, 0x7c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00
};
// 'halfHeart', 12x12px
const unsigned char epd_bitmap_halfHeart [] PROGMEM = {
	0x00, 0x38, 0x7c, 0xfc, 0xfc, 0xf8, 0x08, 0x04, 0x84, 0x44, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00
};
// 'emptyHeart', 12x12px
const unsigned char epd_bitmap_emptyHeart [] PROGMEM = {
	0x00, 0x38, 0x44, 0x84, 0x04, 0x08, 0x08, 0x04, 0x84, 0x44, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00
};

// 'title', 128x64px
const unsigned char epd_bitmap_title [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x3c, 0x3c, 0x3c, 0xfc, 0xfc, 0xf0, 0xf0, 0xc0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x3c, 0x3c, 0x3c, 0xfc, 0xfc, 0xfc, 0xfc, 0x3c, 0x3c, 0x3c, 0x00, 0x00, 0x00, 0x00, 
	0xf0, 0xf8, 0xfc, 0xfc, 0x7c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x00, 0x00, 0x00, 0x00, 
	0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 
	0x00, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc, 0x7c, 0x7c, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0, 0x00, 0x00, 0x00, 
	0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xe0, 0xc0, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3c, 0x3c, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0x03, 0x07, 0x0f, 0x07, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0xff, 0xff, 0x78, 0x78, 0x78, 0x78, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x3f, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 
	0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
