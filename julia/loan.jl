using Pkg
Pkg.add("NPFinancial")
Pkg.add("Printf")
using NPFinancial
using Printf

interest_rate=0.02
term_years=30
loan_amount=337500
monthly_payment = pmt(0.02/12, 30*12, 337500)

@printf("Monthly payment for %d year loan at %f %% interest is \$ %f\n", term_years, interest_rate*100, monthly_payment)
