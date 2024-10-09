#include <iostream>
#include <vector>

std::vector<std::vector<int>> multi_kernel_convolution(
    const std::vector<std::vector<int>>& image,
    const std::vector<std::vector<std::vector<int>>>& kernels) {

  int image_rows = image.size();
  int image_cols = image[0].size();

  // Check if there are exactly 4 kernels
  if (kernels.size() != 4) {
    throw std::invalid_argument("Expected exactly 4 kernels");
  }

  // Assuming all kernels are 3x3 (fixed kernel size)
  const int kernel_size = 3;  // Constant for kernel size

  // Result vector initialization
  std::vector<std::vector<int>> current_image = image;
  std::vector<std::vector<int>> next_image(image_rows - kernel_size + 1,
                                           std::vector<int>(image_cols - kernel_size + 1, 0));

  // Sequentially apply each kernel
  for (int k = 0; k < 4; ++k) {
    for (int i = 0; i < next_image.size(); ++i) {
      for (int j = 0; j < next_image[0].size(); ++j) {
        int sum = 0;
        for (int m = 0; m < kernel_size; ++m) {
          for (int n = 0; n < kernel_size; ++n) {
            // Check for valid image boundaries (avoid out-of-bounds access)
            if (i + m < image_rows && j + n < image_cols) {
              sum += current_image[i + m][j + n] * kernels[k][m][n];
            }
          }
        }
        if(sum > 255) sum = 255;
        if(sum < 0) sum = 0;
        
        next_image[i][j] = sum;
      }
    }
        std::cout << "Resultant matrix:" << std::endl;
        for (int i = 0; i < current_image.size(); ++i) {
        for (int j = 0; j < current_image[0].size(); ++j) {
            std::cout << current_image[i][j] << " ";
            }
            std::cout << std::endl;
             }
             
    // Update current_image to be the result of the current kernel
    current_image = next_image;

    // Prepare next_image for the next kernel
    next_image = std::vector<std::vector<int>>(current_image.size() - kernel_size + 1,
                                               std::vector<int>(current_image[0].size() - kernel_size + 1, 0));

    // Update dimensions for the next iteration
    image_rows = current_image.size();
    image_cols = current_image[0].size();
  }

  return current_image;
}


std::vector<std::vector<int>> create_matrix(int rows, int cols) {
  std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix[i][j] = i * cols + j;  // Fills elements from 0 to 143
    }
  }
  return matrix;
}


int main() {
      int image_rows = 12;
      int image_cols = 12;

    // Create the 12x12 matrix
    std::vector<std::vector<int>> image = create_matrix(image_rows, image_cols);


  std::vector<std::vector<std::vector<int>>> kernels = {
    {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}},
    {{0, 0, 1}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 1, 0}},
    {{0, 1, 1}, {0, 0, 0}, {0, 0, 0}}
  };

  std::vector<std::vector<int>> result = multi_kernel_convolution(image, kernels);

    // Print the resulting matrix (modify for desired output format)
  std::cout << "Resultant matrix:" << std::endl;
  for (int i = 0; i < result.size(); ++i) {
    for (int j = 0; j < result[0].size(); ++j) {
      std::cout << result[i][j] << " ";
    }
    std::cout << std::endl;
  }


  return 0;
}
