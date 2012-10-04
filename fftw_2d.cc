/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

A simple program to perform multi-dimensional FFTs using FFTW
Author: N. Iniyan
e-mail: iniyan@ast.uct.ac.za
Last modified: Oct. 2012
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fftw3.h>

using namespace std;

int main(int argc, char *argv[])
{

 if(argc != 2)
 {
  cout<<"Usage: <prgname> <N (The image will be assumed to have N^2 pixels)>"<<endl;
  return 1;
 }

 int N = atoi(argv[1]);
 int Npixels = pow(N,2);

 fftw_complex *in, *out;
 fftw_plan p;

 //Allocate memory for the input and output arrays.
 in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * Npixels);
 out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * Npixels);
 
 //Create plan for performing 2-D FFT before initializing the input array to avoid FFTW_MEASURE
 //from overwriting the input array. For more on this, refer to FFTW documentation.
 p = fftw_plan_dft_2d(N, N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

 cout<<"The input array is a screen of constant illumination..."<<endl;
 for(int i=0;i<Npixels;i++)
 {
  in[i][0] = 1.0;
  in[i][1] = 0.0;
 }

 //Execute plan
 fftw_execute(p);

 cout<<"For the above input, the output is an impulse function..."<<endl;
 for(int i=0;i<Npixels;i++)
   cout<<"out["<<i<<"]: "<<out[i][0]<<", "<<out[i][1]<<endl;

 fftw_destroy_plan(p);
 fftw_free(in);
 fftw_free(out);

 return 0;
}
