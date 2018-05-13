import pokebase as pb
import csv
from bokeh.core.properties import value
from bokeh.io import show, output_file
from bokeh.models import ColumnDataSource
from bokeh.plotting import figure
from bokeh.transform import factor_cmap
import numpy as np

#create color code for type
typecolor ={
            'poison':   '#551A8B',
            'grass':    '#008000',
            'fire':     '#FF0000',
            'flying':   '#00f9ff',
            'water':    '#0000FF',
            'bug':      '#055105',
            'normal':   '#c5c52b',
            'electric': '#FFFF00',
            'ground':   '#903131',
            'fairy':    '#FFC0CB',
            'fighting': '#400440',
            'psychic':  '#bd8bbd',
            'rock':     '#808080',
            'steel':    '#000000',
            'ice':      '#9595d8',
            'ghost':    '#7b7981',
            'dragon':   '#baba24'
    }



class Dex(object):


    #load the kanto regions and saved into a csv file for other feature
    def initail(self):

        self.dex = pb.NamedAPIResource('pokedex','kanto')

        #for the individual pokemon
        self.dict = self.dex.pokemon_entries
        num = len(self.dict)
        file = open('pokemon_entry.csv', 'w')
        file.write('name\n')
        for x in range(0,num):
            temp =(str(self.dict[x]).split("'name': '",1)[1])
            for j in str(temp):

                if j=="'":
                    file.write('\n')
                    break

                else:
                    file.write(j)
        file.close()
        with open('pokemon_entry.csv') as csvfile:
            reader = csv.DictReader(csvfile)
            file = open('pokemon_dict.csv', 'w')
            file.write('name,'+'height,'+'weight,'+'type1,'+'type2,'+'type3,'+'type4,'+'url\n')
            for z in reader:
                print('loading:'+z['name'])
                temp = pb.pokemon(z['name'])
                file.write(str(z['name'])+',')
                file.write(str(temp.height)+',')
                file.write(str(temp.weight)+',')
                for j in range(0,4):
                    try:
                        write=str(temp.types[j]).split("'name': '",1)[1]
                        for j in str(write):

                            if j == "'":
                                file.write(',')
                                break

                            else:
                                file.write(j)
                    except:
                        file.write('0,')
                writeURL = str(temp.sprites).split("'front_default': '", 1)[1]
                for j in str(writeURL):

                    if j == "'":

                        break

                    else:
                        file.write(j)
                file.write('\n')
            print("loading Pokemons complete!")

    # display the histgram of all the pokemons types in region kanto
    def displayhist(self):
        typeshist={
            'poison': 0,
            'grass': 0,
            'fire': 0,
            'flying': 0,
            'water': 0,
            'bug': 0,
            'normal': 0,
            'electric': 0,
            'ground': 0,
            'fairy': 0,
            'fighting': 0,
            'psychic': 0,
            'rock': 0,
            'steel': 0,
            'ice': 0,
            'ghost': 0,
            'dragon': 0

        }
        with open('pokemon_dict.csv') as csvfile:
            name=[]
            poketype=[]
            color=[]
            color = ['#551A8B',
               '#008000',
                '#FF0000',
               '#00f9ff',
               '#0000FF',
                '#055105',
               '#c5c52b',
           '#FFFF00',
              '#903131',
             '#FFC0CB',
            '#400440',
             '#bd8bbd',
               '#808080',
              '#000000',
               '#9595d8',
               '#7b7981',
            '#baba24']

            reader = csv.DictReader(csvfile)
            for x in reader:
                try:
                    typeshist[str(x['type1'])] += 1
                    typeshist[str(x['type2'])] += 1
                    typeshist[str(x['type3'])] += 1
                    typeshist[str(x['type4'])] += 1
                except:
                    a=0


            for key, value in typeshist.items():
                name.append(key)
                poketype.append(value)



            source = ColumnDataSource(data=dict(name=name, poketype=poketype))
            p = figure(x_range=name, plot_height=350,  title="The histogram of all Pokemon Type")
            p.vbar(x='name', top='poketype', width=0.9, source=source,fill_color=factor_cmap('name', palette=color, factors=name))

            p.xgrid.grid_line_color = None
            p.y_range.start = 0
            p.y_range.end = 40
            p.legend.orientation = "horizontal"
            p.legend.location = "top_center"
            p.xaxis.major_label_orientation = "vertical"

            show(p)


    #This method is to read the csv file saved from initailzed method and diplay the pokemon entered by user
    #with specific details
    def displayPokemon(self):
        pokename=''
        pokenamelist=[]
        height =0
        weight =0
        type1 =''
        type2 =''
        type3 =''
        type4 =''
        url =''
        with open('pokemon_dict.csv') as csvfile:
            reader = csv.DictReader(csvfile)
            print('please enter pokemon name you want loop up:')
            name = input()

            for x in reader:
                if name == x['name']:

                    pokename = x['name']
                    height = x['height']
                    weight = x['weight']
                    type1 =x['type1']
                    type2 =x['type2']
                    type3 = x['type3']
                    type4 = x['type4']
                    url = x['url']

            #plot the pokemon status in bokeh
            output_file("bar_basic.html")



            if pokename !='':

                if type2 != '0':
                    x = 300
                    years = [type1, type2]

                    p = figure(x_range=(0,500), y_range=(0,400), title=pokename)

                    data = {
                            type1: [200],
                            type2: [200]
                            }
                    poketype=[typecolor[type1],typecolor[type2]]
                    source = ColumnDataSource(data=data)

                    p.vbar_stack(years, x=x, width=50, color=poketype, source=source,
                                 legend=[value(x) for x in years])


                    p.y_range.start = 0
                    p.xgrid.grid_line_color = None
                    p.axis.minor_tick_line_color = None
                    p.outline_line_color = None
                    p.legend.location = "top_right"
                    p.legend.orientation = "horizontal"

                    p.text(50, 20, text=["Height:"+height],
                           text_color="firebrick", text_align="center", text_font_size="10pt")
                    p.text(50, 40, text=["Weight:" + weight],
                           text_color="firebrick", text_align="center", text_font_size="10pt")

                    p.image_url(url=[url],
                               x=0, y=50, w=253, h=260, anchor="bottom_left")
                    show(p)



                else:
                    x = 300
                    years = [type1]
                    colors = ["#c9d9d3", "#718dbf"]
                    p = figure(x_range=(0, 500), y_range=(0, 500), title=pokename)

                    data = {
                        type1: [200]

                    }

                    source = ColumnDataSource(data=data)

                    p.vbar(x=x, top=400,width=50,color=typecolor[type1],
                    legend=type1)

                    p.y_range.start = 0
                    p.xgrid.grid_line_color = None
                    p.axis.minor_tick_line_color = None
                    p.outline_line_color = None
                    p.legend.location = "top_right"
                    p.legend.orientation = "horizontal"

                    p.image_url(url=[url],
                                x=0, y=50, w=253, h=260, anchor="bottom_left")



                    p.text(50, 20, text=["Height:" + height],
                           text_color="firebrick", text_align="center", text_font_size="10pt")
                    p.text(50, 40, text=["Weight:" + weight],
                           text_color="firebrick", text_align="center", text_font_size="10pt")

                    p.image_url(url=[url],
                                x=0, y=50, w=253, h=260, anchor="bottom_left")
                    show(p)













            else:
                print("The pokemon you entered is not in the kanto region")

    #method to display the region status of pokemons
    def pokestatus(self):
        with open('pokemon_dict.csv') as csvfile:
            reader = csv.DictReader(csvfile)
            weight=[]
            height=[]
            for x in reader:
                weight.append(int(x['weight']))
                height.append(int(x['height']))

            heightnp = np.array(height)
            weightnp = np.array(weight)
            print("=============================================================>")
            print("The mean height is:  ",np.mean(heightnp))
            print("The standard deviation of height is:  ",np.std(heightnp))
            print("The max height is:  ",np.max(heightnp))
            print("The min height is:  ",np.min(heightnp))
            print("The mean height is:  ", np.mean(weightnp))
            print("The standard deviation of height is:  ", np.std(weightnp))
            print("The max height is:  ", np.max(weightnp))
            print("The min height is:  ", np.min(weightnp))
            print("=============================================================>")











print("loading pokemons......")
num = Dex()
while(1):


    print("Hello Pokemon master please select option below: \n")
    print('option n: If you run this program first time please run this option to download pokemon info first:\n ')
    print("option 1: Look up pokemon\n")
    print('option 2: See pokemon type Histogram\n')
    print("option 3: Display summary stats on Pokemon height and weight from region kant:\n ")
    print("option 4: Quit\n")
    option= str(input())
    if option == '1':
        num.displayPokemon()
    elif option == 'n':
        num.initail()
    elif option == '2':
        num.displayhist()
    elif option == '3':
        num.pokestatus()
    elif option == '4':
        break
    else:
        print('please choose the correct option')
