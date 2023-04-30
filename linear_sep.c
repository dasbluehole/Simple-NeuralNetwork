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
/* test if we can train for linearly separable data set
 * 1-we will create a random data set
 * 2-train a perceptron on that data set
 * 3 try it with a known data to check if it works or not
 */ 
#include "perceptron.h"
int main(int argc, char *argv[])
{
	perceptron a = create(2);
	double wts[2] ={1,1};
	set_weights(&a,wts);
	display(a);
	// train the perceptron
	srandom(time(0));
	double data[2];
	for(int ts = 0; ts <10000; ts++)
	{
		
		data[0]= rand()%100;
		data[1]= rand()%100;
		
		double expected = (data[1]<2*data[0]+1)? 1: 0;
		train(&a,data,expected);
	}
	display(a);
	/* test if the perceptron can 
	 * classify properly or not.
	 */ 
	double inps1[2]={20,2};
	printf("\nis (%lf < 2 x %lf + 1) predicted = %lf\n",inps1[1],inps1[0],predict(a,inps1));
	delete(&a);
	
	return 0;
}
