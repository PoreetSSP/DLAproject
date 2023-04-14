#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

int width, height, numberOfParticles;
int steps = 0;
int MaxSteps = 50000;
int ParticleInit = 0;
bool isFirstMove = true;

std::random_device rd;
std::mt19937 gen(rd());    
std::uniform_int_distribution<> dis(1, 8);

//is particle on the edge of the grid
bool isOnEdge(int i,int j,const std::vector<std::vector<bool>>& grid) {
  if (i <= 0 || i >= height - 1 || j <= 0 || j >= width - 1) return true;
  else {
    return false;
  }
}

//is particle next to other particle?
bool IsAdjacent(int& i,int& j, int& width, int& height, const std::vector<std::vector<bool>>& grid){
  if (i > 0 && grid[i-1][j]) return true;
  if (j > 0 && grid[i][j-1]) return true;
  if (i < height-1 && grid[i+1][j]) return true;
  if (j < width-1 && grid[i][j+1]) return true;
  if (i == height/2 && j == width/2) return true; // check for center element
  if (i > 0 && j > 0 && grid[i-1][j-1] && i-1 == height/2 && j-1 == width/2) return   
    true; // check for top left adjacent element
  if (i > 0 && j < width-1 && grid[i-1][j+1] && i-1 == height/2 && j+1 == width/2) 
    return true; // check for top right adjacent element
  if (i < height-1 && j > 0 && grid[i+1][j-1] && i+1 == height/2 && j-1 == width/2) 
    return true; // check for bottom left adjacent element
  if (i < height-1 && j < width-1 && grid[i+1][j+1] && i+1 == height/2 && j+1 == width/2) return true; // check for bottom right adjacent element
  return false;
}

void MoveParticle(int& i, int& j, std::vector<std::vector<bool>>& grid, bool& isFirstMove){

  if (isFirstMove || isOnEdge(i, j, grid)){
    if (j == 0) {
      j++;
    } else if (j == width - 1) {
      j--;
    } else if (i == 0) {
      i++;
    } else {
      i--;
    }
  } else{
      int prev_i = i;
      int prev_j = j;
      grid[prev_i][prev_j] = false; // remove previous position from grid
     
      int direction = dis(gen);

      if (direction == 1) {
        i++;
      } else if (direction == 2) {
        i++;
        j++;
      } else if (direction == 3) {
        j++;
      } else if (direction == 4) {
        i--;
        j++;
      } else if (direction == 5) {
        i--;
      } else if (direction == 6) {
        i--;
        j--;
      } else if (direction == 7) {
        j--;
      } else {
        i++;
        j--;
      }
  }
   if (i < 0 || i >= height || j < 0 || j >= width) return;  
    grid[i][j] = true;
    
  isFirstMove = false;

}
  

int main(){
  std::cout << "Define the height (m) of the mxn grid: \n";
  std::cin >> height;

  std::cout << "Define the width (n) of the mxn grid: \n";
  std::cin >> width;

  int numberOfEdgeElements = 2 * (width) + 2 * (height - 2);

  std::cout << "Define the number of particles (must be smaller than "
            << numberOfEdgeElements << "): \n";
  std::cin >> numberOfParticles;

  if (numberOfParticles >= numberOfEdgeElements) {
    std::cerr << "Edges are fully filled. Make sure that number of particles < "
                 "2n+2(m-2) \n ";
    return 1;
  }

  // making a 2D boolean matrix with a vector:
  std::vector<std::vector<bool>> grid(height);
  for (int i = 0; i < height; i++) {
    grid[i] = std::vector<bool>(width, false);
  }
  
  // making the center particle true:
  const int x = width / 2;
  const int y = height / 2;
  grid[x][y] = true;

   // Seed the random number generator with the current time
    std::srand(std::time(nullptr));


  while (ParticleInit < numberOfParticles) {
    steps = 0;
    for (int k = 0; k < height; k++){
      int i = 0;
      int j = 0;
      
      //starting position of the particle:
      int side = std::rand() % 4 + 1;  // Generate a random number between 1         and 4
      if (side == 1){ // i , j=0
        // Choose a random row index on the chosen column
          i = std::rand() % (height - 1);
            grid[i][0] = true;
      } else if (side ==2){ //i , j = width -1
          i = std::rand() % (height - 1);
            grid[i][width-1] = true;
      } else if(side == 3){ //i=0, j
        j = std::rand() % (width - 1);
          grid[0][j] = true;
      } else { //i = height -1, j
        j = std::rand() % (width - 1);
          grid[height-1][j] = true;
      }
      
      while (!IsAdjacent(i, j, width,height, grid) && steps < MaxSteps) {
        MoveParticle(i, j, grid, isFirstMove);
        steps++;
      }
        ParticleInit++;
    }
  }

  //print to console
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (grid[i][j]) {
        std::cout << "*";
      } else {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
  
}