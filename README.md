**Option Pricing and Risk Assessment Using Variable Strike Price Functions
**

**1. Introduction
**The goal of this project is to evaluate and compare the effects of Linear and Non-Monotonic strike price functions on option pricing and risk assessment. Using the Black-Scholes framework, we model option prices as solutions to a second-order differential equation, rewritten as a system of first-order ODEs. This project extends to Value-at-Risk (VaR) analysis, quantifying the risk associated with each strike price function. By understanding how dynamic strike prices influence the value and risk of options, the study provides insights into balancing return potential and risk in financial markets.


**2. Methods
**Black-Scholes Model:
A second-order ODE for option pricing is reduced to a system of two first-order equations:

Here, V represents the option value, u=dV/dS​ is the slope, and S is the stock price.
Strike Price Functions:
Linear K(S): K(S) = 0.5S + 20
Non-Monotonic K(S): K(S)=100+20sin(S/50)
Numerical Integration:
The system is solved using the Runge-Kutta 4th Order Method, allowing us to compute V(S) for each strike price function.
Value-at-Risk (VaR):
VaR is calculated for each K(S) to assess the maximum loss at a 95% confidence level.
Visualization:
Combined plots of option prices and VaR for both strike price functions are generated for comparative analysis.



**3. Results
**Option Pricing:
The Linear K(S) produces a smooth and predictable curve, reflecting stable option values.
The Non-Monotonic K(S) also produces a smooth curve without oscillations but exhibits a slower rate of increase in option value for lower stock prices. This highlights how the functional form of K(S) influences option values differently.
VaR Analysis:
The Linear K(S) shows a consistently lower and flatter VaR profile, indicating reduced risk across the range of stock prices. 
The Non-Monotonic K(S) has a higher VaR profile throughout, signifying greater risk due to the sinusoidal nature of the strike price function.  
Key Observations:
Dynamic strike prices, while smooth, can influence risk profiles depending on their functional forms.  
Linear strike prices provide lower and more stable risk metrics, making them suitable for conservative strategies.  
Non-Monotonic strike prices result in a higher risk profile, which may align with speculative investment strategies.




**4. Discussion
**The study highlights how the choice of strike price function influences option valuation and associated risk. Linear K(S) emerges as a more stable and predictable option for pricing and risk analysis, while Non-Monotonic K(S), despite its smooth curve, exhibits a higher risk profile. These results demonstrate the utility of integrating VaR analysis with option pricing models for financial risk management.
5.  Significance of the Project:
This project underscores the importance of dynamic strike price modeling in financial derivatives. By integrating numerical solutions with risk metrics like VaR, the study bridges the gap between theoretical financial modeling and practical risk management. The findings provide actionable insights for investors, enabling them to select strike price strategies aligned with their risk tolerance and financial goals.


**6. Questions Highlighting the Significance
**How do dynamic strike price functions affect the stability and predictability of option pricing models?
Both Linear K(S) and Non-Monotonic K(S) produce smooth option pricing curves, but Linear K(S) results in more predictable and consistent outcomes. Non-Monotonic K(S) introduces variability in the rate of growth, influencing option valuation.




What insights can VaR analysis provide about the risk associated with different strike price functions?
VaR analysis shows that Linear K(S) has a lower and more stable risk profile, suitable for conservative strategies. Non-Monotonic K(S) consistently exhibits a higher risk profile, indicating its suitability for speculative investments.
Which strike price function would be more suitable for conservative investors, and why?
Linear K(S) is preferable due to its lower and more stable risk profile, minimizing potential losses.
How do the results align with the theoretical expectations of the Black-Scholes model?
The results validate the model's ability to handle dynamic strike prices while illustrating the trade-offs between return and risk.
What practical applications can this analysis have in financial markets?
This analysis helps investors select strike price strategies that align with their risk tolerance and financial goals, emphasizing the importance of understanding risk dynamics in derivatives markets.


**7. Conclusion
**This study provides a robust framework for analyzing option pricing under dynamic strike prices. By integrating VaR analysis, it bridges the gap between theoretical models and practical risk management. 
The VaR formula and its results provide actionable insights for investors, helping them select strike price strategies that align with their risk tolerance and market objectives.


Note
Additional VaR analysis was added to the model.
