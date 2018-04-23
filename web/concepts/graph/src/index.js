var Chart = require('chart.js')
var moment = require('moment')


document.addEventListener('DOMContentLoaded', function() {
    create_webhooks()
    var ctx = document.getElementById("myChart")
    var MAX_HISTORY = 10
    var labels = []
    var data = []
    for (i = 0; i < MAX_HISTORY; i++) {
        labels.push(i)
        data.push(0)
    }

    chart = new Chart(ctx, {
        type: 'line',
        labels: labels,
        data: {
            datasets: [{
                label: "data",
                data: data,
                strokeColor: "#f00",
                borderColor: "#f00"
            }]
        },
        options: {
            steppedLine: true,
            scales: {
                xAxes: [{
                    ticks: {
                        min: 0,
                        max: 10,
                        stepSize: 0.5
                    }
                }]
            }
        }
    });
    console.log('created chart')
    function update_graph() {
        console.log('updating graph')
        if (document.getElementById('togglebox').getAttribute('state') == 'true')
            var status = 1
        else
            var status = 0
        console.log('status', status)
        var dataset = chart.data.datasets[0]
        dataset.data.push(status)
        while (dataset.data.length > MAX_HISTORY) {
            dataset.data.shift()
        }
        console.log(dataset.data)
        chart.update()
        setTimeout(update_graph, 1000)
    }
    setTimeout(update_graph, 1000)

    function on_box_toggle(e) {
        var box_button = document.getElementById('togglebox')
        box_button.setAttribute('state', box_button.getAttribute('state') == 'false') 
    }

    function create_webhooks() {
        document.getElementById('togglebox').addEventListener('click', on_box_toggle)
    }
})

