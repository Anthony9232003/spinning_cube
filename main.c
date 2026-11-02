#include <math.h> 
#include <stdio.h>
#include <string.h>
#include <unistd.h>

float A, B, C; 
float cubewidth = 10;
int width = 160, height = 44; 
float zBuffer[160 * 44]; 
char buffer[160 * 44]; 
int backgroundASCIICode = ' ';
int distanceFromCam = 60; 
float K1 = 40; 

float incrementSpeed = 0.6; 

float x, y, z; 
float ooz; 
int xp, yp; 
int idx; 

float calculateX(int i, int j, int k)
{
	return -j * cos(B) * sin(C) + k * sin(B) + i * cos(B) * cos(C); 

}

float calculateY(int i, int j, int k) 
{
	return j * cos(A) * cos(A) - j * sin(A) * sin(B) * sin(C) - k * sin(A) 
		* cos(B) + i * (cos(A) * sin(C) + sin(A) * sin(B) * cos(C));
}

float calculateZ(int i, int j, int k)
{
	return  j * cos(A) * sin(B) * sin(C) + j * sin(A) * cos(C) + k * cos(A) 			
		* cos(B) + i * (sin(A) * sin(C) - cos(A) * sin(B) * cos(C)); 
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch){
	x = calculateX(cubeX, cubeY, cubeZ);
        y = calculateY(cubeX, cubeY, cubeZ); 
        z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam; 

        ooz = 1/z;
        xp = (int)(width/2 + K1 * ooz * x * 2); 
        yp = (int)(height/2 + K1 * ooz * y);

        idx = xp + yp * width;
        if (idx>= 0 && idx < width * height) {
	  if (ooz> zBuffer[idx]) {
            zBuffer[idx] = ooz; 
	    buffer[idx] = ch; 

	  }
	}	
      }

int main() {
        printf("\x1b[23");
        while(1) {
          memset(buffer, backgroundASCIICode, width * height);
          memset(zBuffer, 0, width * height * 4);
          for(float cubeX = - cubewidth; cubeX < cubewidth; cubeX += incrementSpeed) {
            for(float cubeY = - cubewidth; cubeY < cubewidth; cubeY += incrementSpeed){

            } 
          }       
	  printf("\x1b[H"); 
	  for(int k = 0; k < width * height; k++){
	   putchar( k % width ? buffer[k] : 10) ; 
	  } 
        
	  A += 0.005; 
	  B += 0.005; 
	
	}

        return 0; 
}

