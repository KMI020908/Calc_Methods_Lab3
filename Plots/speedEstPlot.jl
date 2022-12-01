using Plotly
using DelimitedFiles 
# График убывания ошибки
layout = Layout(
    height = 600,
    width = 800,
    font_size = 16,
    font_family = "Times New Roman",
    font_color = "black",
    paper_bgcolor = "white",
    plot_bgcolor = "white",
    coloraxis = attr(
      outlinecolor = "black"  
    ),    
    xaxis = attr(
        exponentformat = "power",
        title = attr(
            text = "x"
        ),
        color = "black",
        gridcolor = "black",
        gridwidth = 1,
        zerolinecolor = "black",
        zerolinewidth = 3,
        tickfont = attr(
            size = 15
        )
    ),
    yaxis = attr(
        exponentformat = "power",
        title = attr(
            text = "Порядок убывания ошибки интерполирования"
        ),
        gridcolor = "black",
        gridwidth = 1 ,
        zerolinecolor = "black",
        zerolinewidth = 3,
        tickfont = attr(
            size = 15
        )
    )
)
markerAtt = attr(
            color = "green", 
        )
data = readdlm("D:\\Calc_Methods\\Lab3\\speedEstimate.txt");
intervalX = [data[i] for i in 1 : size(data)[1]]
intervalY = [log2(data[i]) for i in size(data)[1] + 1 : length(data)]
plot(
    scatter(x = intervalX, y = intervalY, mode = "markers", marker = markerAtt),
    layout
)