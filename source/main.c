// Includes
#include <PA9.h>       // Include for PA_Lib

int ColorUpDownControl(int intColor, int intTicks) {
   
	if (Pad.Newpress.Up) {
      if (intColor == 31) {
         intColor = 0;
      } else {
		  intColor++;
   	} 
   } else {
	   if (Pad.Held.Up) {
	      if ((intTicks % 10) == 0) {
		      if (intColor == 31) {
		         intColor = 0;
		      } else {
				  intColor++;
		   	}   
			}   
	   }
   }   
   
   if (Pad.Newpress.Down) {
      if (intColor == 0) {
         intColor = 31;
      } else {
		  intColor--;
   	}   
   } else {
	   if (Pad.Held.Down) {
	      if ((intTicks % 10) == 0) {
		      if (intColor == 0) {
		         intColor = 31;
		      } else {
				  intColor--;
		   	}   
		 	}  	
	   }
	}   
	return intColor;
}
   

// Function: main()
int main(int argc, char ** argv)
{
   
   int intRed = 31;
   int intGreen = 31;
   int intBlue = 31;
   int intTicks = 0;
   
	PA_Init();    // Initializes PA_Lib
	PA_InitVBL(); // Initializes a standard VBL
	
	PA_SetBgPalCol(0, 0, PA_RGB(0, 0, 0));	// set the bottom screen color to black
	
	// This will initialise a 16 bit background on each screen. This must be loaded before any other background.
	// If you need to load this after a backgrounds, you'll have to use PA_ResetBgSys, PA_Init8bit, then reload
	// your backgrounds...
	PA_Init16bitBg(0, 3);
	PA_Init16bitBg(1, 3);
	
	PA_InitText(1, 0); // Text system for top screen
	PA_SetTextCol(1, 31, 31, 31); // Set text color to white
	
	PA_OutputText(1, 1, 1, "Mart Drawing - 16bit");
			
	// Infinite loop to keep the program running
	while (1)
	{
		// Simple draw function, draws on the screen...
		PA_16bitDraw(0, PA_RGB(intRed, intGreen, intBlue));  // Color : full red...
		
		// Button control
		if ((Pad.Newpress.Y) || (Pad.Held.Y)) {
		   intRed = ColorUpDownControl(intRed, intTicks);
		}   
		if ((Pad.Newpress.X) || (Pad.Held.X)) {
		   intGreen = ColorUpDownControl(intGreen, intTicks);
		}   
		if ((Pad.Newpress.A) || (Pad.Held.A)) {
		   intBlue = ColorUpDownControl(intBlue, intTicks);
		}   
		if (Pad.Newpress.Start) {
		   PA_Clear16bitBg(0);
		}
		
		
		// Set the current color on the top screen
		PA_Draw16bitRect(1, 10, 20, 40, 50, PA_RGB(intRed, intGreen, intBlue));
		
		//Increment & reset ticks
		intTicks++;
		if (intTicks > 1000) intTicks = 0;
		
		// Debug Info		
		PA_OutputText(1, 1, 18, "Stylus X = %d  ", Stylus.X);
		PA_OutputText(1, 1, 19, "Stylus Y = %d  ", Stylus.Y);
		PA_OutputText(1, 1, 20, "R = %d  G = %d  B = %d   ", intRed, intGreen, intBlue);
		//PA_OutputText(1, 1, 21, "Ticks = %d   ", intTicks);
		
		PA_WaitForVBL();
	}

	return 0;
} // End of main()  
