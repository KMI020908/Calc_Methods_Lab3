using Plotly
using DelimitedFiles 

methodTypeList = ["Lagrange", "Spline"]
gridTypeList = ["Uniform", "Chebyshev"]

f1(x) = x^2
titlef1 = "y = x²"
f2(x) = 1.0 / (1.0 + x^2)
titlef2 = "y = 1 / (1 + x²)"
f3(x) = 1.0 / atan(1.0 + 10 * x^2)
titlef3 = "y = 1 / arctan(1 + 10x²)"
f4(x) = (4.0 * x^3 + 2.0 * x^2 - 4.0 * x + 2.0) ^ √2 + asin(1.0 / (5.0 + x - x^2)) - 5.0
titlef4 = "y = (4x³ + 2x² - 4x + 2)^√2 + arcsin(1 / 5 + x - x²) - 5"
f5(x) = 1.0
titlef5 = "y = 1"

titleList = [titlef1, titlef2, titlef3, titlef4, titlef5]
funcList = [f1, f2, f3, f4, f5]
 
function getInterpPlot(numOfFunc::Int, methodType::String, gridType::String, funcList, titleList, funcColor::String, plRange = [], h = 600, w = 900)
    numOfFuncString = string(numOfFunc)
    grid = readdlm("D:\\Calc_Methods\\Lab3\\$methodType\\$gridType\\solution$numOfFuncString.txt")
    intervalX = [grid[i] for i in 1 : size(grid)[1]]
    intervalY = [grid[i] for i in size(grid)[1] + 1 : length(grid)]
    n = (size(grid)[1] - 1) / 2
    gridText = ""
    if gridType == "Uniform"
        gridText =   "на равномерной сетке"
    else
        gridText = "на Чебышёвской сетке"
    end
    methodText = ""
    if methodType == "Lagrange"
        methodText = "многочленами Лагранжа"
    else
        methodText = "кубическими сплайнами"
    end
    if plRange == []
        push!(plRange, minimum(intervalY))
        push!(plRange, maximum(intervalY) + maximum(intervalY) / 100)
    end
    layoutOfInterp = Layout(
        font_family = "Time New Roman",
        font_color = "black",
        title = attr(
            paper_bgcolor = "red",
            text = "Интерполирование $methodText $gridText при n = $n",
            font_family = "Times New Roman",
            font_color = "black",
            font_size = 24,
            autosize = false,
        ),
        paper_bgcolor = "white",
        plot_bgcolor = "white",
        coloraxis = attr(
          outlinecolor = "black"  
        ),
        height = h,
        width = w,
        xaxis = attr(
            color = "black",
            gridcolor = "black",
            gridwidth = 1,
            zeroline = true,
            zerolinecolor = "black",
            zerolinewidth = 3,
            linecolor = "black",
            linewidth = 3,
            tickfont = attr(
                size = 15
            ),
            title = attr(
                text = "x",
                font_family = "Times New Roman",
                font_color = "black",
                font_size = 20,
            )
        ),
        yaxis = attr(
            gridcolor = "black",
            exponentformat = "power",
            gridwidth = 1,
            linewidth = 3,
            tickfont = attr(
                size = 15
            ),
            title = attr(
                text = "y",
                font_family = "Times New Roman",
                font_color = "black",
                font_size = 20,
            ),
            zeroline = true,
            zerolinecolor = "black",
            zerolinewidth = 1,
            range = [plRange[1], plRange[2]]
        )
    )
    lineAttr = attr(
        color = funcColor,
        width = 3
    )

    pl = plot(
        scatter(x = intervalX, y =intervalY, mode = "line", line = lineAttr),
        layoutOfInterp
    )

    layoutErr = Layout(
        font_family = "Times New Roman",
        font_color = "black",
        title = attr(
            paper_bgcolor = "red",
            text = "Ошибка интерполирования $methodText в точках при n = $n $gridText",
            font_family = "Times New Roman",
            font_color = "black",
            font_size = 20,
            autosize = false
        ),
        height = h,
        width = w,
        paper_bgcolor = "white",
        plot_bgcolor = "white",
        coloraxis = attr(
          outlinecolor = "black"  
        ),
        xaxis = attr(
            title = attr(
                text = "x",
                font_family = "Times New Roman",
                font_color = "black",
                font_size = 20,
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
            title = attr(
                text = "Ошибка интерполирования",
                font_family = "Times New Roman",
                font_color = "black",
                font_size = 20,
            ),
            gridcolor = "black",
            exponentformat = "power",
            gridwidth = 1 ,
            zerolinecolor = "black",
            zerolinewidth = 3,
            tickfont = attr(
                size = 15
            )   
        )
    );
    
    markerAtt = attr(
            showline = true,
            color = funcColor, 
            line_width=1
        );
    
    errPl = plot(
        scatter(x = intervalX, y = abs.(funcList[numOfFunc].(intervalX) - intervalY), mode = "markers", marker = markerAtt),
        layoutErr
    )

    groupPl = [pl ; errPl]
    titleFunc = titleList[numOfFunc]
    minX = minimum(intervalX)
    maxY = maximum(intervalX)
    relayout!(groupPl, 
        height = h, 
        width = w, 
        font_family = "Time New Roman",
        font_color = "black",
        font_size = 22,
        title_text = "$titleFunc, x ∈ [$minX, $maxY]",
        showlegend = false
    )

    return pl, errPl, groupPl
end

function makeErrorPlot(numOfFunc, methodType::String, gridType::String, titleList, interval, funcColor, plRange = [], h = 600, w = 900)
    numOfFuncString = string(numOfFunc)
    errors = readdlm("D:\\Calc_Methods\\Lab3\\$methodType\\$gridType\\Errors\\error$numOfFuncString.txt")
    titleFunc = titleList[numOfFunc]
    minX = minimum(interval)
    maxX = maximum(interval)
    gridText = ""
    if gridType == "Uniform"
        gridText =   "на равномерной сетке"
    else
        gridText = "на Чебышёвской сетке"
    end
    methodText = ""
    if methodType == "Lagrange"
        methodText = "многочленами Лагранжа"
    else
        methodText = "кубическими сплайнами"
    end
    if plRange == []
        push!(plRange, 0.0)
        push!(plRange, maximum(errors) + maximum(errors) / 100)
    end
    layoutErr = Layout(
        font_family = "Times New Roman",
        font_color = "black",
        title = attr(
            paper_bgcolor = "red",
            text = "Зависимость макс. ошибки интерполирования $methodText $gridText. $titleFunc, x ∈ [$minX, $maxX]",
            font_family = "Times New Roman",
            font_color = "black",
            font_size = 17,
            autosize = false
        ),
        height = h,
        width = w,
        paper_bgcolor = "white",
        plot_bgcolor = "white",
        coloraxis = attr(
          outlinecolor = "black"  
        ),
        xaxis = attr(
            title = attr(
                text = "x",
                font_family = "Times New Roman",
                font_color = "black",
                font_size = 20,
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
            title = attr(
                text = "Ошибка интерполирования",
                font_family = "Times New Roman",
                font_color = "black",
                font_size = 20,
            ),
            gridcolor = "black",
            exponentformat = "power",
            gridwidth = 1 ,
            zerolinecolor = "black",
            zerolinewidth = 3,
            tickfont = attr(
                size = 15
            ),
            range = [plRange[1], plRange[2]]   
        )
    );
    
    markerAtt = attr(
            showline = true,
            color = funcColor, 
            line_width=1
        );
    
    n = length(errors) 
    errPl = plot(
        scatter(x = 1 : n, y = [errors[i] for i in 1 : n], mode = "markers", marker = markerAtt),
        layoutErr
    )

    return errPl
end

function makePlot(numOfFunc, funcList, titleList, interval, funcColor, h = 600, w = 800)
    titleFunc = titleList[numOfFunc]
    minX = minimum(interval)
    maxX = maximum(interval)
    layout = Layout(
        font_family = "Times New Roman",
        font_color = "black",
        title = attr(
            paper_bgcolor = "red",
            text = "$titleFunc, x ∈ [$minX, $maxX]",
            font_family = "Times New Roman",
            font_color = "black",
            font_size = 24,
            autosize = false
        ),
        height = h,
        width = w,
        paper_bgcolor = "white",
        plot_bgcolor = "white",
        coloraxis = attr(
          outlinecolor = "black"  
        ),
        xaxis = attr(
            title = attr(
                text = "x",
                font_family = "Times New Roman",
                font_color = "black",
                font_size = 20,
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
            title = attr(
                text = "y",
                font_family = "Times New Roman",
                font_color = "black",
                font_size = 20,
            ),
            gridcolor = "black",
            exponentformat = "power",
            gridwidth = 1 ,
            zerolinecolor = "black",
            zerolinewidth = 3,
            tickfont = attr(
                size = 15
            )   
        )
    )

    lineAttr = attr(
        color = funcColor,
        width = 3
    )

    plIntervalX = range(minX, stop = maxX, length = 500)
    pl = plot(
        scatter(x = plIntervalX, y = funcList[numOfFunc].(plIntervalX), mode = "line", line = lineAttr),
        layout
    )

    return pl
end

#makeErrorPlot(1, methodTypeList[1], gridTypeList[1], titleList, [-1.0, 1.0], "red")