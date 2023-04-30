/*
 * perceptron.h
 * Implements a single header Library for Perceptron
 * Copyright 2023 Ashok Shankar Das <ashok@localhost.localdomain>
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

#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../smatlib.h"
// structure of our perceptron.
typedef struct perceptron
{
	int n_inp; // number inputs
	matrix W; // weight matrix
	double lr; // learning rate
	double bias; //bias
}perceptron;

/* creates a perceptron and initialize with default value
 * takes number of inputs desired as integer
 * returns a perceptron structure
 */
perceptron create(unsigned int num_inputs)
{
	perceptron p;;
	
	p.n_inp = num_inputs;
	p.W = create_matrix(1,num_inputs); // make row matrix
	p.lr = 0.1;
	for(int c =0; c<p.n_inp; c++)
	{
		set_cell(&p.W,0,c,0.0);
	}
	p.bias = 1.0;
	return p;
}

/* deletes a perceptron
 */ 
void delete(perceptron *p)
{
	delete_matrix(&p->W);
}

/* sets weights in weght matrix
 * accepts pointer to perceptron and weights as array of double
 */ 

void set_weights( perceptron *p, double vals[])
{
	for(int i=0; i<p->n_inp; i++)
	{
		set_cell(&p->W,0,i,vals[i]);
	}
}

/* sets bias 
 * input perceptron pointer and bias value as double
 */
void set_bias(perceptron *p, double bias)
{
	p->bias = bias;
}

/* copy a perceptron
 * takes a perceptron pointer
 * returns a perceptron pointer
 */ 
perceptron copy(perceptron p)
{
	perceptron q = create(p.n_inp);
	for(int i =0;i<p.n_inp; i++)
	{
		set_cell(&q.W,0,i,get_cell(p.W,0,i));
	}
	q.bias = p.bias;
	q.lr = p.lr;
	return q;
}
double sigmoid(double x)
{
	return (1.0/(1.0+exp(-x)));
}
/* calculates/ predicts the output
 * accepts perceptron and array of values as input
 * returns 0.0 - 1.0 based upon classification
 */ 
double predict(perceptron p, double inp[])
{
	double res=0.0;
	
	for(int r = 0; r < p.n_inp; r++)
	{
		res += inp[r]*get_cell(p.W,0,r);
	}
	res += p.bias;
	double ret= sigmoid(res);
	return(ret);
		
}
/* returns bias value */
double get_bias(perceptron p)
{
	return(p.bias);
}
// forward declaration of display
void display(perceptron p);
/* train the perceptron
 * input perceptron pointer, array of data and expected output
 * returns nothing
 * NOTE this function adjusts weights
 */
void train(perceptron *p,double *data,double desired)
{
	double guess = predict(*p,data);
	
	double err = desired - guess;
	for(int n = 0; n<p->n_inp; n++)
	{
		double cur_w = get_cell(p->W,0,n);
		set_cell(&p->W,0,n,cur_w+p->lr*err*data[n]);
	}
	p->bias += p->lr *err;
}
// displays the perceptron
void display(perceptron p)
{
	printf("************Perceptron:**************\n");
	printf("\nnumber of inputs = %d\n",p.n_inp);
	printf("Weights:\n");
	display_matrix(transpose(p.W));
	printf("Bias = %f\n",p.bias);
	printf("*************************************\n");
}
#endif //__PERCEPTRON_H__
