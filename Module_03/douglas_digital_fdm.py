import numpy as np
import matplotlib.pyplot as plt

# Define parameters
S_max = 200  # Maximum stock price
T = 1.0  # Time to maturity (1 year)
K = 100  # Strike price
r = 0.05  # Risk-free rate
sigma = 0.2  # Volatility

# Grid parameters
Ns = 100  # Number of stock price points
Nt = 1000  # Number of time points
ds = S_max / Ns
dt = T / Nt

# Initial condition: digital option payoff
V = np.zeros(Ns + 1)
V[int(K / ds):] = 1

# Boundary conditions
V[0] = 0
V[-1] = 0

# Douglas scheme
A = np.zeros((Ns + 1, Ns + 1))
B = np.zeros((Ns + 1, Ns + 1))

for i in range(1, Ns):
    A[i, i - 1] = 0.5 * dt * (sigma ** 2 * i ** 2 - r * i)
    A[i, i] = -dt * (sigma ** 2 * i ** 2 + r) - 1
    A[i, i + 1] = 0.5 * dt * (sigma ** 2 * i ** 2 + r * i)

    B[i, i - 1] = -0.5 * dt * (sigma ** 2 * i ** 2 - r * i)
    B[i, i] = dt * (sigma ** 2 * i ** 2 + r) - 1
    B[i, i + 1] = -0.5 * dt * (sigma ** 2 * i ** 2 + r * i)

A[0, 0] = A[-1, -1] = 1
B[0, 0] = B[-1, -1] = 1

# Time-stepping
for n in range(1, Nt + 1):
    b = B @ V
    V = np.linalg.solve(A, b)

# Plot the results
S = np.linspace(0, S_max, Ns + 1)
plt.plot(S, V, label='t={:.2f}'.format(T))
plt.xlabel('Stock Price')
plt.ylabel('Option Value')
plt.title('Douglas Method for Digital Option')
plt.legend()
plt.show()

# Print the option price at S = K
print(f"Digital option price at S = {K}: {V[int(K / ds)]}")
