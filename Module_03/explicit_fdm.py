import numpy as np
import matplotlib.pyplot as plt

def explicit_finite_difference(S_max, K, T, r, sigma, M, N, option_type='cash-or-nothing-call', P=1):
    """
    Explicit Finite Difference Method for Digital Option Pricing
    
    Parameters:
    S_max : float  -> Maximum stock price considered
    K : float      -> Strike price
    T : float      -> Time to maturity
    r : float      -> Risk-free rate
    sigma : float  -> Volatility
    M : int        -> Number of stock price steps
    N : int        -> Number of time steps
    option_type : str -> Type of digital option (cash-or-nothing-call, cash-or-nothing-put)
    P : float      -> Payout of the digital option
    """
    # Discretization
    dS = S_max / M  # Stock price step
    dt = T / N      # Time step
    
    # Grid initialization
    S = np.linspace(0, S_max, M+1)
    V = np.zeros((M+1, N+1))
    
    # Boundary and terminal conditions
    if option_type == 'cash-or-nothing-call':
        V[:, -1] = np.where(S > K, P, 0)  # Payoff at maturity
    elif option_type == 'cash-or-nothing-put':
        V[:, -1] = np.where(S < K, P, 0)
    
    # Finite Difference Coefficients
    for j in range(N-1, -1, -1):  # Iterate backward in time
        for i in range(1, M):  # Iterate over stock prices (excluding boundaries)
            delta = (V[i+1, j+1] - V[i-1, j+1]) / (2 * dS)
            gamma = (V[i+1, j+1] - 2 * V[i, j+1] + V[i-1, j+1]) / (dS**2)
            
            A = 0.5 * sigma**2 * S[i]**2 * gamma
            B = r * S[i] * delta
            C = -r * V[i, j+1]
            
            V[i, j] = V[i, j+1] + dt * (A + B + C)  # Explicit step
        
        # Boundary conditions (Dirichlet type)
        V[0, j] = 0  # No value at zero stock price
        V[-1, j] = P * np.exp(-r * (T - j * dt))  # Upper boundary approximation
    
    return S, V[:, 0]  # Return initial time values

# Parameters
S_max = 200   # Maximum stock price
K = 100       # Strike price
T = 1         # Time to maturity (1 year)
r = 0.05      # Risk-free rate
sigma = 0.2   # Volatility
M = 100       # Stock price steps
N = 1000      # Time steps

# Compute Digital Option Price using Explicit FDM
S_values, V_values = explicit_finite_difference(S_max, K, T, r, sigma, M, N, option_type='cash-or-nothing-call', P=1)

# Find the index corresponding to the initial stock price S0
S0 = 100
index_S0 = np.where(S_values == S0)[0][0]

# Print the price of the digital call option
print('The price of the digital call option is', V_values[index_S0])

# Plot the results
plt.figure(figsize=(8,5))
plt.plot(S_values, V_values, label='Digital Call Option Price', color='b')
plt.axvline(K, linestyle='--', color='r', label='Strike Price')
plt.xlabel('Stock Price (S)')
plt.ylabel('Option Value (V)')
plt.title('Explicit Finite Difference Method - Digital Call Option')
plt.legend()
plt.grid()
plt.show()
