import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg

# Define parameters
S_max = 200  # Maximum stock price
T = 1.0  # Time to maturity (1 year)
K = 100  # Strike price
r = 0.05  # Risk-free rate
sigma = 0.2  # Volatility

# Grid parameters
Ns = 800  # Increased stock price points for better accuracy
Nt = 8000  # Increased time steps for better accuracy
ds = S_max / Ns
dt = T / Nt

# Stock price grid (non-uniform for better accuracy near K)
S = np.linspace(0, S_max, Ns + 1) ** 1.5  # Adjusted spacing
S /= S.max() / S_max  # Normalize to original scale

# Initial condition: digital option payoff (1 if S > K, else 0)
V = np.zeros(Ns + 1)
V[np.searchsorted(S, K):] = 1  # More precise strike placement

# Boundary conditions
V[0] = 0  # At S = 0, option is worthless
V[-1] = np.exp(-r * T)  # Properly discounted boundary condition

# Richardson extrapolation scheme matrices
A = np.zeros((Ns + 1, Ns + 1))
B = np.zeros((Ns + 1, Ns + 1))

# Fill matrices A and B (interior points only)
for i in range(1, Ns):
    alpha = 0.25 * dt * (sigma ** 2 * ((S[i]) ** 2) / (ds ** 2) - r * S[i] / ds)
    beta = -0.5 * dt * (sigma ** 2 * ((S[i]) ** 2) / (ds ** 2) + r)
    gamma = 0.25 * dt * (sigma ** 2 * ((S[i]) ** 2) / (ds ** 2) + r * S[i] / ds)

    A[i, i - 1] = -alpha
    A[i, i] = 1 - beta
    A[i, i + 1] = -gamma

    B[i, i - 1] = alpha
    B[i, i] = 1 + beta
    B[i, i + 1] = gamma

# Apply boundary conditions to A and B matrices
A[0, 0] = A[-1, -1] = 1
B[0, 0] = B[-1, -1] = 1

# Precompute LU decomposition of A
lu, piv = scipy.linalg.lu_factor(A)

# Time-stepping with Richardson extrapolation
for n in range(1, Nt + 1):
    b = B @ V
    V_half = scipy.linalg.lu_solve((lu, piv), b)
    b = B @ V_half
    V_full = scipy.linalg.lu_solve((lu, piv), b)
    V = np.maximum(0, np.minimum(1, 2 * V_full - V_half))  # Ensure stability

# Plot the results
plt.figure(figsize=(8, 5))
plt.plot(S, V, label=f'Digital Option at T={T:.2f}')
plt.axvline(K, linestyle='--', color='r', label='Strike Price')
plt.xlabel('Stock Price')
plt.ylabel('Option Value')
plt.title('Richardson Extrapolation Method for Digital Option')
plt.legend()
plt.grid()
plt.show()

# Print the option price at S = K
digital_option_price_at_K = V[np.searchsorted(S, K)]
print(f"Digital option price at S = {K}: {digital_option_price_at_K:.4f}")
