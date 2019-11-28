document.addEventListener("DOMContentLoaded", function () {

    new QWebChannel(qt.webChannelTransport, function (channel) {
        window.bridge = channel.objects.UIBridge;

        bridge.onLoad();

        setMapBounds();
    });
});

let attribution = '';
let token = 'pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw';
let map = L.map('map').setView([48.745158, 9.106606], 13);
let routeLayer = L.layerGroup([]).addTo(map);
let graphLayer = L.layerGroup([]).addTo(map);
let popup = L.popup();

let start = '';
let stop = '';
let graphShown = false;
let graphData = [];

L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={token}', {
    maxZoom: 20,
    attribution: '',
    id: 'mapbox.streets',
    token: token
}).addTo(map);

map.on("click", onMapClick);
map.on("zoomend", onZoomEnd);
map.on("mouseup", onMouseUp);

function onMapClick(e) {
    let latlng = e.latlng.lat.toFixed(6).toString() + "," + e.latlng.lng.toFixed(6).toString();

    let start = "<button onclick='setStart(\"" + latlng + "\")'>Set start</button>";
    let stop = "<button onclick='setStop(\"" + latlng + "\")'>Set stop</button>";

    popup.setLatLng(e.latlng)
        .setContent("What's here?<br> " + latlng + "<br>" + start + "<br>" + stop)
        .addTo(map);
}

function onZoomEnd(e) {
    //setMapBounds();
}

function onMouseUp(e) {
    //setMapBounds();
}

// JS -> C++

function setMapBounds() {
    let bounds = map.getBounds();
    let sw = bounds["_southWest"];
    let ne = bounds["_northEast"];

    bridge.setMapBounds(ne.lat, ne.lng, sw.lat, sw.lng);
}

function setStart(latlon)
{
    bridge.setStart(latlon);
}

function setStop(latlon)
{
    bridge.setStop(latlon);
}

// C++ -> JS

function setView(lat, lon) {
    map.setView([lat, lon], map.getZoom());
}

function setShowGraph(bool) {
    graphShown = bool;

    showGraph();
}

function setGraph(graph) {
    graphData = graph;
}

function showGraph() {
    if(!graphShown)
        graphLayer.clearLayers();

    if(graphShown) {
        let nodeColor = 'rgba(255, 255, 0, 0.25)';
        let edgeColor = 'rgba(255, 50, 0, 0.25)';

        for (let index = 0; index < graphData.length; ++index) {
            for (let edge = 0; edge < graphData[index].length; ++edge) {

                // if (graph[index].length >= 1) {
                //     L.circle(graph[index][0], {
                //         radius: 1,
                //         color: nodeColor,
                //         interactive: false
                //     }).addTo(graphLayer);
                // }

                if (graphData[index].length === 2) {
                    // L.circle(graph[index][1], {
                    //     radius: 1,
                    //     color: nodeColor
                    // }).addTo(graphLayer);

                    L.polyline(graphData[index], {color: edgeColor, interactive: false}).addTo(graphLayer);
                }
            }
        }
    }
}

function showRoute(lines) {
    routeLayer.clearLayers();

    routeLayer.addLayer(L.geoJSON({
        type: "LineString",
        coordinates: lines
    }, {
        style: {
            color: "rgba(0, 150, 255, 0.75)",
            weight: 4
        }
    }));
}
