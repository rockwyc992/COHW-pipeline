#執行環境
    make、g++、Linux

#編譯方式
    make

#執行方式
    make run

#程式架構
    分成fetch、decode、exetute、memory、write(back)五個模組
    其中分成data跟runtime兩個部分，data會將這個模組執行的結果暫存起來
    runtime會從前一個階段的暫存值(類似IF/ID、ID/EX、EX/MEM)
    
