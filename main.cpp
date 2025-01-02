#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cpgplot.h>

// Black-Scholes parameters
const double sigma = 0.2;  // Volatility
const double r = 0.05;     // Risk-free rate

// Linear K(S) function
double linearK(double S) {
    return 0.5 * S + 20; // Linear dependency
}

// Non-monotonic K(S) function
double nonMonotonicK(double S) {
    return 100 + 20 * std::sin(S / 50); // Non-monotonic oscillation
}

// System of first-order ODEs
double dV(double S, double u) {
    return u; // dV/dS = u
}

double du(double S, double V, double u, double K) {
    if (S <= 0.0) return 0.0; // Avoid division by zero
    return (r * V - sigma * sigma * S * u) / S; // Second equation: du/dS
}

// Runge-Kutta 4th Order Method
void rungeKutta(double S_start, double S_end, double h, std::vector<float>& S_vals, std::vector<float>& V_vals, double (*K_func)(double)) {
    double S = S_start;
    double V = std::max(S - K_func(S), 0.0); // Payoff for a European call option
    double u = 1.0; // Initial slope

    while (S <= S_end) {
        S_vals.push_back(S);
        V_vals.push_back(V);

        double K = K_func(S);
        double k1_v = h * dV(S, u);
        double k1_u = h * du(S, V, u, K);

        double k2_v = h * dV(S + h / 2.0, u + k1_u / 2.0);
        double k2_u = h * du(S + h / 2.0, V + k1_v / 2.0, u + k1_u / 2.0, K);

        double k3_v = h * dV(S + h / 2.0, u + k2_u / 2.0);
        double k3_u = h * du(S + h / 2.0, V + k2_v / 2.0, u + k2_u / 2.0, K);

        double k4_v = h * dV(S + h, u + k3_u);
        double k4_u = h * du(S + h, V + k3_v, u + k3_u, K);

        V += (k1_v + 2 * k2_v + 2 * k3_v + k4_v) / 6.0;
        u += (k1_u + 2 * k2_u + 2 * k3_u + k4_u) / 6.0;

        S += h;
    }
}

// Compute VaR
void computeVaR(const std::vector<float>& V_vals, double confidence, std::vector<float>& VaR_vals) {
    std::vector<float> losses;
    for (size_t i = 0; i < V_vals.size(); ++i) {
        losses.push_back(-V_vals[i]); // Convert to losses
    }
    std::sort(losses.begin(), losses.end());

    size_t index = static_cast<size_t>((1.0 - confidence) * losses.size());
    for (size_t i = 0; i < losses.size(); ++i) {
        VaR_vals.push_back(i <= index ? losses[index] : losses[i]);
    }
}

// Combined Plot Function
void plotCombined(const std::vector<float>& S_vals_1, const std::vector<float>& Y_vals_1, const std::vector<float>& S_vals_2, const std::vector<float>& Y_vals_2,
                  const char* title, const char* label1, const char* label2, int color1, int color2) {
    if (!cpgopen("/XWINDOW")) return;

    cpgscr(0, 0, 0, 0); // Black background
    cpgscr(1, 1, 1, 1); // White foreground
    cpgslw(2);          // Line width
    cpgsch(1.5);        // Text size

    // Determine combined Y-axis limits
    float min_Y = std::min(*std::min_element(Y_vals_1.begin(), Y_vals_1.end()), *std::min_element(Y_vals_2.begin(), Y_vals_2.end()));
    float max_Y = std::max(*std::max_element(Y_vals_1.begin(), Y_vals_1.end()), *std::max_element(Y_vals_2.begin(), Y_vals_2.end()));

    cpgenv(S_vals_1.front(), S_vals_1.back(), min_Y, max_Y, 0, 1);
    cpglab("Stock Price (S)", "Option Value / VaR", title);

    // Plot first dataset
    cpgsci(color1);
    cpgline(S_vals_1.size(), S_vals_1.data(), Y_vals_1.data());
    cpgptxt(S_vals_1.back() - 60, max_Y - 15, 0.0, 0.0, label1);

    // Plot second dataset
    cpgsci(color2);
    cpgline(S_vals_2.size(), S_vals_2.data(), Y_vals_2.data());
    cpgptxt(S_vals_2.back() - 0, max_Y - 10, 0.0, 0.0, label2);

    cpgclos();
}




int main() {
    // Parameters
    double S_start = 50.0;
    double S_end = 150.0;
    double h = 1.0;
    double confidence = 0.95;

    // Linear K(S)
    std::vector<float> S_vals_linear, V_vals_linear, VaR_vals_linear;
    rungeKutta(S_start, S_end, h, S_vals_linear, V_vals_linear, linearK);
    computeVaR(V_vals_linear, confidence, VaR_vals_linear);

    // Non-Monotonic K(S)
    std::vector<float> S_vals_nonMonotonic, V_vals_nonMonotonic, VaR_vals_nonMonotonic;
    rungeKutta(S_start, S_end, h, S_vals_nonMonotonic, V_vals_nonMonotonic, nonMonotonicK);
    computeVaR(V_vals_nonMonotonic, confidence, VaR_vals_nonMonotonic);

    // Combined Option Pricing Plot
    plotCombined(S_vals_linear, V_vals_linear, S_vals_nonMonotonic, V_vals_nonMonotonic, 
                 "Option Pricing - Linear vs Non-Monotonic K(S)", 
                 "Linear K(S)", "Non-Monotonic K(S)", 2, 7);

    // Combined VaR Plot
    plotCombined(S_vals_linear, VaR_vals_linear, S_vals_nonMonotonic, VaR_vals_nonMonotonic, 
                 "VaR - Linear vs Non-Monotonic K(S)", 
                 "VaR Linear", "VaR Non-Monotonic", 4, 5);

    return 0;
}
