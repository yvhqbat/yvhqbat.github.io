#!/usr/bin
class Animal(object):
    def run(self):
        print('animal is running...');

class Dog(Animal):
    #pass
    def run(self):
        print('dog is running...')

class Cat(Animal):
    #pass
    def run(self):
        print('cat is running')

a=Animal()
d=Dog()
c=Cat()

a.run()
d.run()
c.run()

def Run(animal):
    print('this is Run()')
    animal.run()

Run(a)
Run(d)
Run(c)

print(type(a))
print(type(Animal))

print(type(int))
print(13)

print('hello')

print(isinstance(a, Animal))

#dir()
l=dir(a)
for element in l:
    print(element)


#Student
class Student(object):
    count=13
    def __init__(self, name):
        #count = count+1
        self.__name=name

    def get_name(self):
        return self.__name

l=[]
for i in range(0,10):
    l.append(Student(i))

for element in l:
    print(element.get_name(), element.count)

