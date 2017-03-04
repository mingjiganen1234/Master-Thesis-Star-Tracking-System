#include <stdio.h>
#include <math.h>
#include <xparameters.h>
#include <xCCLabel.h>
#include "platform.h"

unsigned int float_to_u32(float val) {
	unsigned int result;
	union float_bytes {
		float v;
		unsigned char bytes[4];
	} data;
	data.v = val;

	result = (data.bytes[3] << 24) + (data.bytes[2] << 16) + (data.bytes[1] << 8) + (data.bytes[0]);
	return result;
}

float u32_to_float(unsigned int val) {
	union {
		float val_float;
		unsigned char bytes[4];
	} data;
	data.bytes[3] = (val >> (8*3)) & 0xff;
	data.bytes[2] = (val >> (8*2)) & 0xff;
	data.bytes[1] = (val >> (8*1)) & 0xff;
	data.bytes[0] = (val >> (8*0)) & 0xff;
	return data.val_float;
}

int main() {
	init_platform();

	//Initialize IP core
	int status;
	XCclabel cCLabel;
	XCclabel_Config *cCLabel_cfg;

	cCLabel_cfg = XCclabel_LookupConfig(XPAR_CCLABEL_0_DEVICE_ID);
	if (!cCLabel_cfg) {
		printf("Error loading config\n");
	}
	status = XCclabel_CfgInitialize(&cCLabel,cCLabel_cfg);
	if (status != XST_SUCCESS) {
		printf("Error initializing\n");
	}
	XCclabel_EnableAutoRestart(&cCLabel);

	/********************************************** SOFTWARE ****************************************************************/





	/********************************************** HARDWARE ****************************************************************/
	// Input

	//Start IP core
	XCclabel_Start(&cCLabel);

	// Wait until it's done
	while(!XCclabel_IsDone);

	//Output


















	cleanup_platform();
	return 0;
}
