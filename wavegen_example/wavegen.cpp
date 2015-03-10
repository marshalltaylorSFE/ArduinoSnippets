#include "math.h"
#include "wavegen.h"
#include "arduino.h"

//--------------------------------------------------------------------------------------
// Generates a single sample of a 256 sample long waveform
//
// char shape is SINESHAPE, PULSESHAPE, RAMPSHAPE, or DCSHAPE
// float duty, float amp
// char sample is 0x00 to 0xFF
//
// Shapes are ~ +-127, scaled by amp/100, then output ranged 0 to 255 (but type int)
int get_sample(uint8_t shape, float amp, float duty, uint8_t sample)
{
	int ret_val;
	float ret_calc_var1;
	
	switch ( shape )
	{
	case SINESHAPE:
		//use the cmath (math.h) header
		//This function could be faster if some of the conversion was offloaded
		ret_calc_var1 = 0x7F * sin(((float)sample * 3.141592)/128);
		break;
	case PULSESHAPE:
		//Is sample beyond duty cycle?
		if (sample > (uint8_t)(255 * duty))
		{
			//is later than duty
			ret_calc_var1 = -127;
		}
		else
		{
			//is earlier
			ret_calc_var1 = 128;
		}
	    break;
	case RAMPSHAPE:
		//essentially returns input sample
		ret_calc_var1 = 127 * (((float)sample/255) - 0.5);
	    break;
	case DCSHAPE:
		//Will use amplitude as DC setting
		ret_calc_var1 = 0;
	    break;
	default:
	    break;
	}

	//Provide scaling and center here
	if ((amp > 1)||(amp <= 0))
	{
		//Invalid amp.  Set to 1 but say nothing.
		amp = 1;
	}

	// Scale here
	ret_calc_var1 = ret_calc_var1 * amp;
        ret_calc_var1 = ret_calc_var1 + 0x7F;

	//cast
	ret_val = (unsigned int)ret_calc_var1;


	return ret_val;
}

