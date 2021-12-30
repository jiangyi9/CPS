flight_data = csvread("flight.log",1);
plot(flight_data(:,1), flight_data(:,2)); % plot height
xlabel("time (s)")
ylabel("height (m)")

%find if there is a overshot
find_index_overshot = find(flight_data(:,2) > 1, 1);
if exist(find_index_overshot,'var')
    disp("There is overshot!");
else 
    disp("There is no overshot!");
end
    
%find the settle time
find_index_settle = find(flight_data(:,2) < 0.98, 1, 'last');
fprintf('The settle time is %f\n',flight_data(find_index_settle, 1));