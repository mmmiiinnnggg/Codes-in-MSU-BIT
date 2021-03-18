filename = "parcifier-1.xlsx";
%filename = "dryer-1.xlsx";
%filename = "microwave-1.xlsx";
tbl = readtable(filename,'TextType','string');
head(tbl)%head of xlsx
str = tbl.reviewText;%the reviews text
documents = tokenizedDocument(str);
documents(1:5)
%compoundScores is the result vector
compoundScores=vaderSentimentScores(documents)
compoundScores(1:5)
for i = 1:18939
    compoundLength(i) = length(char(str(i)))
end
compoundLengthTran = transpose(compoundLength)