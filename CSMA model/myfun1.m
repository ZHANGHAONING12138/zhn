function F = myfun1(input)
p = input(1);
tau = input(2);
global W m n
sum = 0;

for k = 0 : m - 1
    sum = sum + (2 * p).^k;
end
global s
s = (1 - (2 * p).^m) / (1 - 2 * p);
F(1) = 1 - (1 - tau).^(n-1) - p;
F(2) = 2 / (1 + W + p * W .* s) - tau;
end