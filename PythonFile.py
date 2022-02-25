import re
import string
import os.path
from os import path

#Description:
# To call this function, pass the function name into the CallProcedure function.
#Example:
# callProcedure("CountAll");
#Output:
#Return:
# None
def CountAll():
    text = open('CS210_Project_Three_Input_File.txt', 'r') #open and read text file
    dictionary = dict() #empty dictionary to store words
    for line in text:
        line = line.strip() #strip whitspace
        word = line.lower() #convert all char to lower
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1 #increment number of times the word appears
        else:
            dictionary[word] = 1 #if word is not in the dictionary, add it with a value of 1
    for key in list (dictionary.keys()): 
       print(key.capitalize(), ":", dictionary[key])
    text.close() #close file

#Description:
# To call this function, pass this function into the CallIntFunc function along with the desired search term.
#Example:
# callIntFunc("CountInstances", searchTerm);
#Output:
# Returns the number of occurrances of the desired search term.
#Return:
# int wordCount
def CountInstances(searchTerm):
    searchTerm = searchTerm.lower()
    text = open('CS210_Project_Three_Input_File.txt', 'r')
    wordCount = 0 #variable to track number of times word has been found 
    for line in text:
        line = line.strip() 
        word = line.lower()
        if word == searchTerm: #make sure word found is equal to user input
            wordCount += 1
    text.close()
    return wordCount

def CollectData():
    text = open('CS210_Project_Three_Input_File.txt', 'r+')
    frequency = open('frequency.dat', 'w+') #create and write frequency.dat
    dictionary = dict()
    for line in text:
        line = line.strip()
        word = line.lower()
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1
        else:
            dictionary[word] = 1
    for key in dictionary: #write key and value to frequency.dat
        frequency.write(key.capitalize() + " " + str(dictionary[key]) + "\n")
    text.close()
    frequency.close()