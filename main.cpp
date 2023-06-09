#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

int width, height, numberOfParticles;
int i = 0;
int j = 0;
int steps = 0;
int ParticleInit = 0;

std::random_device rd;
std::mt19937 gen(rd());    
std::uniform_int_distribution<> dis(1, 8);

//is particle on the edge of the grid
bool isOnEdge(int i,int j) {
  if (i == 0 || i == height - 1 || j == 0 || j == width - 1) return true;
  else {
    return false;
  }
}

bool inBounds(int i, int j){
  if (i > 0 && i < height - 1 && j > 0 && j < width - 1) return true;
  return false;
}

//is particle next to center particle?
bool hasDeadNeighbour(int i, int j, const std::vector<std::vector<bool>>& grid) {
  // Check if the particle is adjacent to the center particle
    std::vector<std::pair<int, int>> coordsToCheck { //make a pair of 2 displacements di en dj
        {1, 0}, {0, -1}, {0, 1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} 
    };

    for (std::pair<int, int> coords : coordsToCheck) { //loopt over elk element van de array  //loop variabele : vector
        if (inBounds(i+coords.first,j + coords.second) && grid[i + coords.first][j + coords.second]) { //bv grid[height/2 +1][width/2 +0]
            return true;
        }
    }
    return false;
}


void MoveParticle(int& i, int& j, std::vector<std::vector<bool>>& grid){
 
  if (isOnEdge(i, j)){
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
   if (hasDeadNeighbour(i, j, grid)) {
        grid[i][j] = true;
      }
}
  

int main(){
  std::cout << "Define the height (m) of the mxn grid: \n";
  std::cin >> height;

  std::cout << "Define the width (n) of the mxn grid: \n";
  std::cin >> width;

  std::cout << "Define the number of particles: \n";
  std::cin >> numberOfParticles;

  // making a 2D boolean matrix with a vector:
  std::vector<std::vector<bool>> grid(height);
  for (int i = 0; i < height; i++) {
    grid[i] = std::vector<bool>(width, false);
  }
  
  // making the center particle true:
  const int m = height/ 2;
  const int n = width / 2;
  grid[m][n] = true;

   // Seed the random number generator with the current time
    std::srand(std::time(nullptr));

  while (ParticleInit < numberOfParticles) {
   steps = 0;
    for (int k = 0; k < numberOfParticles; k++){
      i = 0;
      j = 0;
       
      //starting position of the particle:
      int side = (std::rand() % 4) + 1;  // Generate a random number between 1 and 4
      if (side == 1){ // i , j=0
        // Choose a random row index on the chosen column
          i = std::rand() % (height);
      } else if (side ==2){ //i , j = width -1
          i = std::rand() % (height);
      } else if(side == 3){ //i=0, j
        j = std::rand() % (width);
      } else { //i = height -1, j
        j = std::rand() % (width);
      }
      
      while (!hasDeadNeighbour(i,j,grid)) {
        MoveParticle(i, j, grid);
        steps++;
        //print to console
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
