import numpy as np
import scipy.linalg

def fully_implicit_digital_option(S_max, K, T, r, sigma, M, N, P=1):
    """
    Fully Implicit Finite Difference Method for Digital Option Pricing.
    
    Parameters:
    S_max : float  -> Maximum stock price considered
    K : float      -> Strike price
    T : float      -> Time to maturity
    r : float      -> Risk-free rate
    sigma : float  -> Volatility
    M : int        -> Number of stock price steps
    N : int        -> Number of time steps
    P : float      -> Payout of the digital option

    Returns:
    S: Array of stock prices
    V: Digital option prices at t=0
    """
    # Use a logarithmic grid to better capture digital option behavior near K
    S = np.exp(np.linspace(np.log(1), np.log(S_max), M+1))

    dS = np.diff(S)  # Variable step sizes
    dt = T / N       # Constant time step

    V = np.zeros(M+1)  # Option price at each stock price

    # Digital option payoff (cash-or-nothing call: 1 if S > K, else 0)
    V[:] = np.where(S >= K, P, 0)

    # Coefficients for Fully Implicit Method
    j = np.arange(1, M)  # Interior points
    alpha = 0.5 * dt * (sigma**2 * (S[1:M]**2) / dS[:-1]**2 - r * S[1:M] / (2 * dS[:-1]))
    beta = 1 + dt * (sigma**2 * (S[1:M]**2) / dS[:-1]**2 + r)
    gamma = 0.5 * dt * (sigma**2 * (S[1:M]**2) / dS[:-1]**2 + r * S[1:M] / (2 * dS[:-1]))

    # Construct matrix A for implicit step
    A = np.zeros((M-1, M-1))
    np.fill_diagonal(A, beta)  # Main diagonal
    np.fill_diagonal(A[1:], -alpha[:-1])  # Sub-diagonal
    np.fill_diagonal(A[:, 1:], -gamma[:-1])  # Super-diagonal

    # Precompute LU decomposition of A
    lu, piv = scipy.linalg.lu_factor(A)

    # Time-stepping (backward in time)
    for j in range(N-1, -1, -1):
        d = V[1:M]  # Right-hand side of the equation

        # Solve the system using LU decomposition
        V[1:M] = scipy.linalg.lu_solve((lu, piv), d)

        # Apply boundary conditions
        V[0] = 0  # If S = 0, digital option is worthless
        V[-1] = P * np.exp(-r * (T - j * dt))  # Cash-or-nothing decay

    return S, V

# Compute Digital Option Price using Fully Implicit Method
M_implicit = 500   # More stock price steps for better accuracy
N_implicit = 2000  # More time steps for better resolution

# Define parameters for digital option pricing
S_max = 200   # Maximum stock price
K = 100       # Strike price
T = 1         # Time to maturity (1 year)
r = 0.05      # Risk-free rate
sigma = 0.2   # Volatility

S_values_implicit, V_values_implicit = fully_implicit_digital_option(
    S_max, K, T, r, sigma, M_implicit, N_implicit, P=1
)

# Find the index corresponding to the initial stock price S0
index_S0_implicit = np.argmin(np.abs(S_values_implicit - K))
digital_option_price_implicit = V_values_implicit[index_S0_implicit]

print(digital_option_price_implicit)