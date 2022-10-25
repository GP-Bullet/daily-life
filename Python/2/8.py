a,b =map(int,input().split(" "))
c = float(( a - b ) * 100.0 / b )
if c<10 :
    print('OK')
elif (c>=10) and (c<50):
    print('Exceed %.0f%s. Ticket 200'%(c,'%'))
else:
    print('Exceed %.0f%s. License Revoked'%(c,'%'))