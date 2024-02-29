import QtQuick 2.15
import QtCharts 2.15

ChartView {
    height: 480
    width: 640
    antialiasing: true

    title: "Temperature History"
    theme: ChartView.ChartThemeQt

    LineSeries {
        id: temperatureSeries
        name: "Temperature"

        axisX: timeAxis
        axisY: temperatureAxis

    }

    ValuesAxis {
        id: timeAxis
    }

    ValuesAxis {
        id: temperatureAxis
        min: 15
        max: 25
    }

    Connections {
        target: temperatureData
        onNewReading: {
            if (temperatureSeries.count > 120){
                temperatureSeries.remove(0);
            }


            temperatureSeries.append(temperatureData.lastReading.x, temperatureData.lastReading.y)

            timeAxis.min = temperatureSeries.at(0).x
            timeAxis.max = temperatureSeries.at(temperatureSeries.count-1).x

            if(temperatureData.lastReading.y < temperatureAxis.min) {
                temperatureAxis.min = temperatureData.lastReading.y;
            }
            if (temperatureData.lastReading.y > temperatureAxis.max) {
                temperatureAxis.max = temperatureData.lastReading.y;
            }

        }
    }
}


