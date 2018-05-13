#This programing is going to take the 2018 NBA All Star player display their status, and other infomation like number of player
#played all star game for each team
#Programer: Qing Cheng
#Date: 4/16/2018

from bokeh.core.properties import value
from bokeh.io import show, output_file
from bokeh.models import ColumnDataSource,LabelSet
from bokeh.plotting import figure
from bokeh.transform import dodge
import pandas as pd

#This method is display the individual player's status including current season and carrer average,
#it will also showing the image of player and their team wining rate
def playerstatus(name):
    try:
        x_label=['PPG','RPG','APG','BPG']
        status =[]
        carrer=[]

        #taking the status data into the player's dict
        status.append(df.loc[df['Names'] == name, 'PPG'].iloc[0])
        status.append(df.loc[df['Names'] == name, 'RPG'].iloc[0])
        status.append(df.loc[df['Names'] == name, 'APG'].iloc[0])
        status.append(df.loc[df['Names'] == name, 'BPG'].iloc[0])

        carrer.append(df.loc[df['Names'] == name, 'CPPG'].iloc[0])
        carrer.append(df.loc[df['Names'] == name, 'CRPG'].iloc[0])
        carrer.append(df.loc[df['Names'] == name, 'CAPG'].iloc[0])
        carrer.append(df.loc[df['Names'] == name, 'CBPG'].iloc[0])



        data = {'Data': x_label,
                'Current Season': status,
                'Carrer': carrer,
                }

        #plot the data using the bokeh API with status, picture, position and team rate
        source = ColumnDataSource(data=data)

        p = figure(x_range=x_label, y_range=(0, 32), plot_height=600, plot_width=800, title=name)

        p.vbar(x=dodge('Data', -0.1, range=p.x_range), top='Current Season', width=0.2, source=source,
           color="#c9d9d3", legend=value("Current Season"))

        p.vbar(x=dodge('Data', 0.1, range=p.x_range), top='Carrer', width=0.2, source=source,
           color="#718dbf", legend=value("Carrer"))

        p.image_url(url=[str(df.loc[df['Names'] == name, 'image'].iloc[0])],
                x=3,y=15,  w=1, h=10, anchor="bottom_left")

        p.text(3.35, 14, text=["Team: " + df.loc[df['Names'] == name, 'Team'].iloc[0]],
               text_color="firebrick", text_align="center", text_font_size="10pt")

        p.text(3.35, 13, text=["Position : " + df.loc[df['Names'] == name, 'Position'].iloc[0]],
               text_color="firebrick", text_align="center", text_font_size="10pt")

        p.text(3.35, 12, text=["Team Wining Rate : " + str(df.loc[df['Names'] == name, 'Wining Rate'].iloc[0])],
               text_color="firebrick", text_align="center", text_font_size="10pt")

        labels1 = LabelSet(x='Data', y='Current Season', text='Current Season',
                           x_offset=-35, y_offset=0,source=source, render_mode='canvas')

        labels2 = LabelSet(x='Data', y='Carrer', text='Carrer',
                           source=source, render_mode='canvas')



        p.legend.location = "top_right"

        p.y_range.start = 0

        p.xaxis.major_label_orientation = 1
        p.xgrid.grid_line_color = None

        p.add_layout(labels1)
        p.add_layout(labels2)

        show(p)
    #error handling
    except:
        print("Please enter the correct payer's name, see the player list for reference")



#This method is allow you to choose two player and display their current status at one graph
def compare(p1,p2):
    try:
        x_label = ['PPG', 'RPG', 'APG', 'BPG']
        name1_status=[]
        name2_status=[]

        #store both two player's tatus into dictionary
        name1_status.append(df.loc[df['Names'] == p1, 'PPG'].iloc[0])
        name1_status.append(df.loc[df['Names'] == p1, 'RPG'].iloc[0])
        name1_status.append(df.loc[df['Names'] == p1, 'APG'].iloc[0])
        name1_status.append(df.loc[df['Names'] == p1, 'BPG'].iloc[0])

        name2_status.append(df.loc[df['Names'] == p2, 'PPG'].iloc[0])
        name2_status.append(df.loc[df['Names'] == p2, 'RPG'].iloc[0])
        name2_status.append(df.loc[df['Names'] == p2, 'APG'].iloc[0])
        name2_status.append(df.loc[df['Names'] == p2, 'BPG'].iloc[0])


        data = {'Data': x_label,
            'p1': name1_status,
            'p2': name2_status,
            }

        #plot both two player head to head in one graph using bokeh
        source = ColumnDataSource(data=data)

        p = figure(x_range=x_label, y_range=(0, 40), plot_height=600, plot_width=800, title="Player Comparsion")

        p.vbar(x=dodge('Data', -0.1, range=p.x_range), top='p1', width=0.2, source=source,
           color="#c9d9d3", legend=value(name1))


        p.vbar(x=dodge('Data', 0.1, range=p.x_range), top='p2', width=0.2, source=source,color="#718dbf", legend=value(name2))

        p.image_url(url=[str(df.loc[df['Names'] == p1, 'image'].iloc[0])],
                x=0.9, y=20, w=1, h=10, anchor="bottom_left")

        p.text(1.3, 19, text=['Team Win Rate:'+str(df.loc[df['Names'] == name1, 'Wining Rate'].iloc[0])],
           text_color="firebrick", text_align="center", text_font_size="10pt")

        p.text(2, 20, text=['VS'],
           text_color="firebrick", text_align="center", text_font_size="25pt")

        p.image_url(url=[str(df.loc[df['Names'] == p2, 'image'].iloc[0])],
                x=2.1, y=20, w=1, h=10, anchor="bottom_left")

        p.text(2.5, 19, text=['Team Win Rate:' + str(df.loc[df['Names'] == p2, 'Wining Rate'].iloc[0])],
           text_color="firebrick", text_align="center", text_font_size="10pt")

        labels1 = LabelSet(x='Data', y='p1', text='p1',
                          x_offset=-35, y_offset=0, source=source, render_mode='canvas')

        labels2 = LabelSet(x='Data', y='p2', text='p2',
                           source=source, render_mode='canvas')


        p.legend.location = "top_right"

        p.y_range.start = 0

        p.xaxis.major_label_orientation = 1
        p.xgrid.grid_line_color = None

        p.add_layout(labels1)
        p.add_layout(labels2)

        show(p)
    except:
        print("Please enter the correct payer's name, see the player list for reference")


#display the number of player for each team in the console window as well as display player's name
def team_report():

    team ={
        'Boston Celtics':0,
        'Toronto Raptors':0,
        'Cleveland Cavaliers':0,
        'Philadelphia 76ers':0,
        'Milwaukee Bucks':0,
        'Washington Wizards':0,
        'Miami Heat':0,
        'Indiana Pacers':0,
        'New York Knicks':0,
        'Detroit Pistons':0,
        'Charlotte Hornets':0,
        'Golden State Warriors':0,
        'Houston Rockets':0,
        'New Orleans Pelicans':0,
        'Oklahoma City Thunder':0,
        'Portland Trail Blazers':0,
        'Minnesota Timberwolves':0,
        'San Antonio Spurs':0

    }
    name=[

        'Boston Celtics',
        'Toronto Raptors',
        'Cleveland Cavaliers',
        'Philadelphia 76ers',
        'Milwaukee Bucks',
        'Washington Wizards',
        'Miami Heat',
        'Indiana Pacers',
        'New York Knicks',
        'Detroit Pistons',
        'Charlotte Hornets',
        'Golden State Warriors',
        'Houston Rockets',
        'New Orleans Pelicans',
        'Oklahoma City Thunder',
        'Portland Trail Blazers',
        'Minnesota Timberwolves',
        'San Antonio Spurs'

    ]

    rate=[]

    #counting the player in each team
    for x in df['Team']:
        team[x] +=1

    print("Report of number of plater in each team played 2018 NBA All Star: ")
    for x in team.keys():
        print(x+': '+str(team[x])+'\n'+"Player: \n"+str(df.loc[df['Team'] == x]['Names'])+'\n')

    for y in team.keys():
        rate.append(float(df.loc[df['Team'] == y]['Wining Rate'].iloc[0]))

    data ={
        'name':name,
        'rate':rate}

    #plot the team wining rate using Bokeh API
    source = ColumnDataSource(data=data)

    p = figure(x_range=name, y_range=(0, 1), plot_height=600, plot_width=800, title="Team Plot of Wining Rate")
    p.vbar(x=dodge('name', 0.1, range=p.x_range), top='rate', width=0.2, source=source, color="#718dbf")
    p.y_range.start = 0
    p.xaxis.major_label_orientation = 1
    p.xgrid.grid_line_color = None
    show(p)









#read csv file and store into pandas data frame
df = pd.read_csv('NBA_AllStar_data.csv')

answer=""
#creating a whole loop and display the main page for user to choose what to display
while answer !='5':
    print("*********************************************************************")
    print("Hello User Please enter the option number you want to see!          *")
    print("1.Check all star players status                                     *")
    print("2.Status Compare between two players                                 *")
    print("3.Report of players in each team played in all star game            *")
    print("4.Exit program                                                      *")
    print("*********************************************************************")
    #taking the option
    answer = str(input())
    if answer == '1':
        print('Player list:')
        print("Kyrie Irving")
        print("DeMar DeRozan")
        print("LeBron James")
        print("Joel Embiid")
        print("Giannis Antetokounmpo")
        print("Bradley Beal")
        print("Goran Dragic")
        print("Al Horford")
        print("Kevin Love")
        print("Kyle Lowry")
        print("Victor Oladipo")
        print("Kristaps Porzingis")
        print("John Wall")
        print("Andre Drummond")
        print("Kemba Walker")
        print("Stephen Curry")
        print("James Harden")
        print("Kevin Durant")
        print("DeMarcus Cousins")
        print("Anthony Davis")
        print("Russell Westbrook")
        print("Damian Lillard")
        print("Draymond Green")
        print("Karl-Anthony Towns")
        print("LaMarcus Aldridge")
        print("Klay Thompson")
        print("Jimmy Butler")
        print("Paul George")
        print("please enter your player name(Caution with capital letter!): ")
        name = str(input())
        playerstatus(name)
    elif answer == '2':
        print('Player list:')
        print("Kyrie Irving")
        print("DeMar DeRozan")
        print("LeBron James")
        print("Joel Embiid")
        print("Giannis Antetokounmpo")
        print("Bradley Beal")
        print("Goran Dragic")
        print("Al Horford")
        print("Kevin Love")
        print("Kyle Lowry")
        print("Victor Oladipo")
        print("Kristaps Porzingis")
        print("John Wall")
        print("Andre Drummond")
        print("Kemba Walker")
        print("Stephen Curry")
        print("James Harden")
        print("Kevin Durant")
        print("DeMarcus Cousins")
        print("Anthony Davis")
        print("Russell Westbrook")
        print("Damian Lillard")
        print("Draymond Green")
        print("Karl-Anthony Towns")
        print("LaMarcus Aldridge")
        print("Klay Thompson")
        print("Jimmy Butler")
        print("Paul George")
        print("please enter your player name: ")
        print("Please enter the first player's name(Caution with capital letter!): ")
        name1 = str(input())
        print("Please enter the second player's name(Caution with capital letter!): ")
        name2 =str(input())
        compare(name1,name2)

    elif answer =='3':
        team_report()


    elif answer =='4':
        break;
    else:
        print("Please enter the correct option")




