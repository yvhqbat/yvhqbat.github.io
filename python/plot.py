import matplotlib.pyplot as plt

labels='frogs','hogs','dogs','logs'
sizes=15,20,45,10
colors='yellowgreen','gold','lightskyblue','lightcoral'
explode=0,0.1,0,0
plt.pie(sizes,explode=explode,labels=labels,colors=colors,autopct='%1.1f%%',shadow=True,startangle=50)
plt.axis('equal')
plt.show()

plt.plot(range(0,10))
plt.xlabel('x label')
plt.ylabel('y label')
plt.show()

x=[0,3,5,6,9,11,15]
y=[0,1.5,6.2,3,2,5,3]
plt.plot(x,y,'r')
plt.axis([0,20,0,10])
plt.grid(True)
plt.title('grid test')
plt.show()

