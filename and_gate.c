/* Copyright 2023 Ashok Shankar Das <ashok@localhost.localdomain>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include "perceptron.h"

/* this code will show AND gate operation using single perceptron */

int main(int argc, char *argv[])
{
	// AND gate implementation.
	// x1 x2 y
	//  0  0 0
	//  0  1 0
	//  1  0 0
	//  1  1 1
	//
	//  0,1---\----1,1
	//   |      \    |
	//   |        \  |
	//   |          \|
	//   |           |\<-line separating  our data 
	//  0,0-------1,0
	
	// so our perceptron will have 2 inputs and one output
	perceptron ag = create(2);
	display(ag);
	double inp[2];
	double des;
	for(int ts=0; ts<10000; ts++)
	{
		inp[0]=0.0;
		inp[1]=0.0;
		des = 0.0;
		train(&ag, inp, des);
		inp[0]=1.0;
		inp[1]=0.0;
		des = 0.0;
		train(&ag, inp, des);
		inp[0]=0.0;
		inp[1]=1.0;
		des = 0.0;
		train(&ag, inp, des);
		inp[0]=1.0;
		inp[1]=1.0;
		des = 1.0;
		train(&ag, inp, des);
	}
	display(ag);
	// training complete
	// test it now
	inp[0]=0;
	inp[1]=0;
	printf("inputs %d, %d predicted = %f\n",(int)inp[0],(int)inp[1],predict(ag,inp));
	inp[0]=1;
	inp[1]=0;
	printf("inputs %d, %d predicted = %f\n",(int)inp[0],(int)inp[1],predict(ag,inp));
	inp[0]=0;
	inp[1]=1;
	printf("inputs %d, %d predicted = %f\n",(int)inp[0],(int)inp[1],predict(ag,inp));
	inp[0]=1;
	inp[1]=1;
	printf("inputs %d, %d predicted = %f\n",(int)inp[0],(int)inp[1],predict(ag,inp));
	
	delete(&ag);
	return(0);
}
