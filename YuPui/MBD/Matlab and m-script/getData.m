%% Import data from text file.
% Script for importing data from the following text file:
%
%    C:\Users\yupuic\Documents\MATLAB\Sensor_record_20180403_082203_AndroSensor.csv
%
% To extend the code to different selected data or a different text file,
% generate a function instead of a script.
% Auto-generated by MATLAB on 2018/04/03 16:56:03 - YuPui

%% Initialize variables.
filename = 'C:\Users\yupuic\Documents\MATLAB\Sensor_record_20180403_082203_AndroSensor.csv';
delimiter = ';';
startRow = 3;

%% Read columns of data as text:
% For more information, see the TEXTSCAN documentation.
formatSpec = '%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%[^\n\r]';

%% Open the text file.
fileID = fopen(filename,'r');

%% Read columns of data according to the format.
% This call is based on the structure of the file used to generate this
% code. If an error occurs for a different file, try regenerating the code
% from the Import Tool.
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'TextType', 'string', 'HeaderLines' ,startRow-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');

%% Close the text file.
fclose(fileID);

%% Convert the contents of columns containing numeric text to numbers.
% Replace non-numeric text with NaN.
raw = repmat({''},length(dataArray{1}),length(dataArray)-1);
for col=1:length(dataArray)-1
    raw(1:length(dataArray{col}),col) = mat2cell(dataArray{col}, ones(length(dataArray{col}), 1));
end
numericData = NaN(size(dataArray{1},1),size(dataArray,2));

for col=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,30]
    % Converts text in the input cell array to numbers. Replaced non-numeric
    % text with NaN.
    rawData = dataArray{col};
    for row=1:size(rawData, 1)
        % Create a regular expression to detect and remove non-numeric prefixes and
        % suffixes.
        regexstr = '(?<prefix>.*?)(?<numbers>([-]*(\d+[\,]*)+[\.]{0,1}\d*[eEdD]{0,1}[-+]*\d*[i]{0,1})|([-]*(\d+[\,]*)*[\.]{1,1}\d+[eEdD]{0,1}[-+]*\d*[i]{0,1}))(?<suffix>.*)';
        try
            result = regexp(rawData(row), regexstr, 'names');
            numbers = result.numbers;
            
            % Detected commas in non-thousand locations.
            invalidThousandsSeparator = false;
            if numbers.contains(',')
                thousandsRegExp = '^\d+?(\,\d{3})*\.{0,1}\d*$';
                if isempty(regexp(numbers, thousandsRegExp, 'once'))
                    numbers = NaN;
                    invalidThousandsSeparator = true;
                end
            end
            % Convert numeric text to numbers.
            if ~invalidThousandsSeparator
                numbers = textscan(char(strrep(numbers, ',', '')), '%f');
                numericData(row, col) = numbers{1};
                raw{row, col} = numbers{1};
            end
        catch
            raw{row, col} = rawData{row};
        end
    end
end


%% Split data into numeric and string columns.
rawNumericColumns = raw(:, [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,30]);
rawStringColumns = string(raw(:, [28,29,31]));


%% Replace non-numeric cells with NaN
R = cellfun(@(x) ~isnumeric(x) && ~islogical(x),rawNumericColumns); % Find non-numeric cells
rawNumericColumns(R) = {NaN}; % Replace non-numeric cells

%% Make sure any text containing <undefined> is properly converted to an <undefined> categorical
for catIdx = [1,2]
    idx = (rawStringColumns(:, catIdx) == "<undefined>");
    rawStringColumns(idx, catIdx) = "";
end

%% Allocate imported array to column variable names
ACCELEROMETERXms = cell2mat(rawNumericColumns(:, 1));
ACCELEROMETERYms = cell2mat(rawNumericColumns(:, 2));
ACCELEROMETERZms = cell2mat(rawNumericColumns(:, 3));
GRAVITYXms = cell2mat(rawNumericColumns(:, 4));
GRAVITYYms = cell2mat(rawNumericColumns(:, 5));
GRAVITYZms = cell2mat(rawNumericColumns(:, 6));
LINEARACCELERATIONXms = cell2mat(rawNumericColumns(:, 7));
LINEARACCELERATIONYms = cell2mat(rawNumericColumns(:, 8));
LINEARACCELERATIONZms = cell2mat(rawNumericColumns(:, 9));
GYROSCOPEXrads = cell2mat(rawNumericColumns(:, 10));
GYROSCOPEYrads = cell2mat(rawNumericColumns(:, 11));
GYROSCOPEZrads = cell2mat(rawNumericColumns(:, 12));
LIGHTlux = cell2mat(rawNumericColumns(:, 13));
MAGNETICFIELDXT = cell2mat(rawNumericColumns(:, 14));
MAGNETICFIELDYT = cell2mat(rawNumericColumns(:, 15));
MAGNETICFIELDZT = cell2mat(rawNumericColumns(:, 16));
ORIENTATIONZazimuth = cell2mat(rawNumericColumns(:, 17));
ORIENTATIONXpitch = cell2mat(rawNumericColumns(:, 18));
ORIENTATIONYroll = cell2mat(rawNumericColumns(:, 19));
PROXIMITYi = cell2mat(rawNumericColumns(:, 20));
SOUNDLEVELdB = cell2mat(rawNumericColumns(:, 21));
LOCATIONLatitude = cell2mat(rawNumericColumns(:, 22));
LOCATIONLongitude = cell2mat(rawNumericColumns(:, 23));
LOCATIONAltitudem = cell2mat(rawNumericColumns(:, 24));
LOCATIONAltitudegooglem = cell2mat(rawNumericColumns(:, 25));
LOCATIONSpeedKmh = cell2mat(rawNumericColumns(:, 26));
LOCATIONAccuracym = cell2mat(rawNumericColumns(:, 27));
LOCATIONORIENTATION = categorical(rawStringColumns(:, 1));
Satellitesinrange = categorical(rawStringColumns(:, 2));
Timesincestartinms = cell2mat(rawNumericColumns(:, 28));
YYYYMODDHHMISS_SSS = rawStringColumns(:, 3);


%% Clear temporary variables
clearvars filename delimiter startRow formatSpec fileID dataArray ans raw col numericData rawData row regexstr result numbers invalidThousandsSeparator thousandsRegExp rawNumericColumns rawStringColumns R catIdx idx;


xPos = degToMiles(LOCATIONLongitude);
yPos = degToMiles(LOCATIONLatitude);
plot(xPos, yPos);

%% Helper function convert lat/log degs to miles and centralize it to inital position 
function  pos = degToMiles(degs)
    pos = degs*69;
    initPos = pos(1);
    pos = pos-initPos;
end
