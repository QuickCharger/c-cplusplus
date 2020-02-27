cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(PATTERN)

#creational
# Creates an instance of several families of classes
add_subdirectory(abstractFactoryModel)
# Separates object construction from its representation
add_subdirectory(builder)
# Creates an instance of several derived classes
add_subdirectory(factoryMethod)
# Avoid expensive acquisition and release of resources by recycling objects that are no longer in use
add_subdirectory(objectPool)
# A fully initialized instance to be copied or cloned
add_subdirectory(prototype)
# A class of which only a single instance can exist
add_subdirectory(singleton)

#structural
# Match interfaces of different classes
add_subdirectory(adapter)
# Separates an object's interface from its implementation
add_subdirectory(bridge)
# A tree structure of simple and composite objects
add_subdirectory(composite)
# Add responsibilities to objects dynamically
add_subdirectory(decorator)
# A single class that represents an entire subsystem
add_subdirectory(facade)
# A fine-grained instance used for efficient sharing
add_subdirectory(flyweight)
# Restricts accessor/mutator access
add_subdirectory(privateClassData)
# An object representing another object
add_subdirectory(proxy)

#behavioral
add_subdirectory(chainOfResponsibility)
add_subdirectory(command)
add_subdirectory(interpreter)
add_subdirectory(iterator)
add_subdirectory(mediator)
add_subdirectory(memento)
add_subdirectory(nullObject)
add_subdirectory(observer)
add_subdirectory(state)
add_subdirectory(strategy)
add_subdirectory(templateMethod)
add_subdirectory(visitor)
