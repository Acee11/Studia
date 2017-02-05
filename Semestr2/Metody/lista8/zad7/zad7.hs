data Nat = Zero | Succ Nat
(+), (*), (^) :: Nat -> Nat -> Nat
m + Zero = m
m + Succ n = Succ (m + n)
m * Zero = Zero
m * Succ n = (m * n) + m
m ^ Zero = Succ Zero
m ^ Succ n = (m ^ n) * m