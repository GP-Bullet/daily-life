distance=int(input())
walk=distance/1.2
bike=distance/3.0+27+23
if walk<bike:
    print("Walk")
elif walk>bike:
    print("Bike")
else:
    print("All")