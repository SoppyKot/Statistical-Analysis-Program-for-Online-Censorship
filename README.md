# Statistical-Analysis-Program-for-Online-Censorship
This program uses statistics to judge the authenticity of online content.

Given below is the algorithm employed in the code.

Input 1: Info of Reported content
Input 2: Reporters’ Info 

System’s job: 
1)	 1st Filtering: 
	
Read the number of views for the content (from input 1).
Count no. of reports for that content.
If it fits in a ratio x:y (platform’s decision) , Go for 2nd filtering                
 else the post is not inappropriate

2)	2nd filtering: (to find out whether this is a religious issue)

Count 1 = no of reporters from X religion
Count 2 = no of reporters from Y religion
Count 3 = Number of reporters from Z religion
If count 1 >= count 2

Count = count 1
Else count  = count 2
If count 2 >= count 3
Count = count 2 
Else 
Count = count 3

If count > x% of total reports ,( value of x is again defined by the platform itself)
 We can conclude that this is truly a spam which is majorly reported by people of religion Z

If we don’t find a clear majority in religion criteria.
We conclude that the issue is not a religious issue

Then we further go on to check for majorities in various other categories (* that we get from the reporter’s personal info i.e., input 2) like Gender of the reporter , region , if they follow any one famous  personality, etc etc etc

Now, for reports that specify the posts as fake or which contain violence, we simply could declare them as confirmed spam if they are declared the same for more than 60%(for example) of the total reports because these can’t enter our scrutinizing procedure as we can’t conclude that they are confirmed spam just from reporter’s info 


Program usage instructions:
The program is written in C and needs to be compiled first.
After compilation, run the program through the command line by providing the two text files as arguments.
The first argument should be the file in which information about the content  is present and the second argument should be the file which contains information about the users who have reported that particular content.
