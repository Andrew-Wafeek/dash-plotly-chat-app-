###############################################################################
#                     ESP Chat Application - IOT Application                  #
#                                                                             #
###############################################################################
import dash
from dash.dependencies import Output, Event, Input
import dash_core_components as dcc
import dash_html_components as html
import socket
import select

#Connect to server##
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
   
host = '172.28.130.90'
port = 80  

s.connect((host, port))

inout = [s]

class values(object):
    coming_str = ""
    input_str = ""
    data = ""
    

def sendstr(data):
    data = str(data)
    for i in range(len(data)):
        s.send(data[i].encode())

def printst(data):
    data = str(data)
    for i in range(len(data)):
        print(data[i])

##Background Design##
external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']
app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
colors = {
    'background': '#111111',
    'text': '#7FDBFF'
}
app.layout = html.Div(style={'backgroundColor': colors['background'],'height': '600'}, 
                     children=[
                     html.H1(children='ESP Chat',style={'text-align':'center','color': colors['text']}),
                     html.Div(id='output-keypress'),
                     html.Div(dcc.Textarea(id='output-box',readOnly = 'true',style={'width': '500','height':'250'}),
                              style={'margin':'1px auto','text-align':'center'}),
                     html.Div([
                               dcc.Input(id='input-box',value="",style={'width': '350','height':'25px','margin':'10px'}),
                               html.Button('Send', id='button',style={'width':'120px','height':'50px','margin':'10px'}),
                               dcc.Interval(id='update_text',interval= 200)],
                               style={'margin':'1px auto','text-align':'center','width':'1210px'}),     
                     ])
                    
@app.callback(
    dash.dependencies.Output('output-keypress', 'children'),
    [dash.dependencies.Input('button', 'n_clicks')],
    [dash.dependencies.State('input-box', 'value')])
def upload_appinput(n_clicks, value):
    sendstr(value)
    return ""

@app.callback(
    dash.dependencies.Output('output-box', 'value'),
    events=[Event('update_text', 'interval')])
def update_espText():
    infds, outfds, errfds = select.select(inout, inout, [], 5)
    if len(infds) != 0:
        values.coming_str = s.recv(255).decode('utf-8')
        values.data = values.data + values.coming_str 
    else:
        print("No data received")
    #values.coming_str = s.recv(1024).decode('utf-8')
        

    return "{} \n".format(values.data)

if __name__ == '__main__':
    app.run_server()