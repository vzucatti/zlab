
#include <iostream>
#include <cmath>
#include <tuple>

#include "math.hpp"

template <zlab::VectorConcept T>
std::tuple<zlab::ZMatrix, zlab::ZVector> 
vandermondeMatrix_and_targetVector(const T&, const T&);

int main(){
    using namespace std;
    using namespace zlab;
    
    // --------------------------------------------------------------------------------
    // PROBLEM: Polynomial Curve Fitting (Cubic: y = c0 + c1*x + c2*x^2 + c3*x^3)
    // Goal: Use Least Squares to recover the known coefficients (c0, c1, c2, c3).
    // The system is overdetermined: A*x = b.
    // --------------------------------------------------------------------------------
    
    cout << "--- Testing Linear Least Squares (Polynomial Fit) ---\n";
    
    // --- KNOWN INPUTS (The Analytical Truth) ---
    // The coefficients we must recover (x = [c0, c1, c2, c3])
    const vector<scalarType> trueCoefficients = {1.0, -0.5, 0.2, -0.01};
    // The x-values used to build the Vandermonde matrix A (X data points)
    const vector<scalarType> dataPoints = {-1.0, 0.0, 1.0, 2.0, 3.0, 4.0};
    
    auto [A, b] = vandermondeMatrix_and_targetVector(trueCoefficients, dataPoints);
    
    ZVector computedCoefficients(trueCoefficients.size());
    linear_least_squares(A, b, computedCoefficients); 
    
    auto errorVector = computedCoefficients.copy();
    axpy(-1.0, trueCoefficients, errorVector); // errorVector -= trueCoefficients
    auto errorNorm = norm(errorVector);
    
    cout << "\nExpected coefficients:\n";
    for(auto& ci : trueCoefficients) cout << ci << " ";
    cout << "\n\nComputed coefficients:\n";
    for(auto i=0; i<trueCoefficients.size(); ++i) cout << computedCoefficients[i] << " ";
    cout << "\n\nCoefficients L2 Error: " << errorNorm << "\n";
    return 0;
}

template <zlab::VectorConcept T>
std::tuple<zlab::ZMatrix, zlab::ZVector>
vandermondeMatrix_and_targetVector(const T& trueCoefficients, const T& dataPoints){
    auto M = dataPoints.size();
    auto N = trueCoefficients.size();
    zlab::ZMatrix A(M, N);
    zlab::ZVector b(M);
    for(auto i = 0; i < M; ++i) {
        for(auto j = 0; j < N; ++j) {
            A(i,j) = zlab::pow(dataPoints[i],j);
            // Calculate b_i based on the true coefficients
            b[i] += trueCoefficients[j] * A(i,j);
        }
    }
    return std::make_tuple(std::move(A),std::move(b));
}
