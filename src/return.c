#include<stdio.h>
#include<stdlib.h>

#include"initialise.h"
#include"io.h"
#include"motion.h"
#include"events.h"
#include"functions.h"
#include"landing.h"

Rocket F9[2]	= {{0.3, 10.52, 20000, 390000, 0}, {0.3, 10.52, 4900, 75700, 1200}};
Engine M1D	= {282, 311, 650000, 720000};
Engine M1Dv	= {0, 345, 0, 801000};

int 	_release = 0, _pitch = 0,
	_MEI1 = 0, _MEI2 = 0, _MEI3 = 0,
	_MECO1 = 0, _MECO2 = 0, _MECO3 = 0,
	_LBURN = 0, _BBURN = 0,
	_SEI1 = 0, _SECO1 = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

	int touch = 0;

	int i, N;
	Event *event;

	init(&event, &N, argc, argv);

/*************************************************************************************************/
/*	Launch/Pitch Kick/Gravity turn				*/
/*	First Stage: Flip/Entry burn/Landing burn		*/
/*************************************************************************************************/

	FILE *f, *f1, *f2;
	f = fopen("Stage1.dat", "w");
	f1 = fopen("Points.dat", "w");
	f2 = fopen("Stage2.dat", "w");

	do{

		/*	Execute events		*/
		for(i=0;i<N;i++) {
			if(event[i].stage == 0 && fabs(t-event[i].t) < dt/2)	// If an Stage1 event in profile.txt occurs at
				execute(event[i].name, f1);			// this time, execute the event
			if(event[i].stage == 1 && fabs(t-event[i].t) < dt/2)	// Stage2 events
				execute(event[i].name, f1);
		}

		/*	End Landing Burn	*/
		if((F9[0].Mf < 5 || (_LBURN && S[0]-Re < 0.01)) && !_MECO3) {	// If Alt = 0.1m or Fuel runs out
			output_telemetry("MECO-3", f1, 0);
			MSECO(0, &_MECO3);
			_LBURN = 0;
		}

		/*	Touchdown		*/
		else if(_release && S[0]<Re && !touch) {			// If Alt = 0.0m
			output_telemetry("Touchdown", NULL, 0);
			touch = 1;
			dt = 0.1;
		}

		/*	SECO1			*/
		else if((F9[1].Mf < 5 || VA[1] > sqrt(G*Me/S[1])) && !_SECO1) {
			output_telemetry("SECO-1", f1, 1);
			MSECO(1, &_SECO1);
		}

		/*	Advance First stage	*/
		if(!touch) {
			leapfrog_step(0);
			output_file(0, f);
		}

		/*	Advance Second stage	*/
		if(_MECO1) {
			leapfrog_step(1);
			output_file(1, f2);
		}

		t += dt;

	}
	while(!touch);
	printf("\n");

	free(event);

	fclose(f);
	fclose(f1);
	fclose(f2);

	return 0;
}
