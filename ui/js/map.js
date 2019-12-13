class UIMap {
    constructor(cpp_ui_map, ll_map) {
        this.cpp_ui_map = cpp_ui_map;
        this.map = ll_map;

        this.map.l_map.on("click", this.onMapClick);
    }

    onMapClick(e) {
        let map = window.map;
        let ui_map = window.ui_map;

        let latlng = e.latlng.lat.toFixed(6).toString() + "," + e.latlng.lng.toFixed(6).toString();

        let start = "<button onclick='ui_map.setStart(\"" + latlng + "\")'>Set start</button>";
        let stop = "<button onclick='ui_map.setStop(\"" + latlng + "\")'>Set stop</button>";

        map.l_popup.setLatLng(e.latlng)
            .setContent(start + "&nbsp;" + stop)
            .addTo(map.l_map);
    }

    // JS -> C++

    onLoad() {
        this.cpp_ui_map.onLoad();
    }

    // setMapBounds() {
    //     let bounds = this.map.l_map.getBounds();
    //     let sw = bounds["_southWest"];
    //     let ne = bounds["_northEast"];
    //
    //     this.ui_bridge.setMapBounds(ne.lat, ne.lng, sw.lat, sw.lng);
    // }

    setStart(latlon) {
        this.cpp_ui_map.setStart(latlon);
    }

    setStop(latlon) {
        this.cpp_ui_map.setStop(latlon);
    }

    // C++ -> JS

    setView(lat, lon) {
        this.map.setView(lat, lon);
    }

    setGraph(graph) {
        this.map.setGraph(graph);
    }

    showGraph(bool) {
        this.map.showGraph(bool);
    }

    showRoute(route) {
        this.map.showRoute(route);
    }
}

class UIGraph {
    constructor(cpp_ui_graph, map) {
        this.cpp_ui_graph = cpp_ui_graph;
        this.map = map;

        this.graphs = {
            "motorway" : this.cpp_ui_graph.motorway,
            "trunk" : [],
            "primary" : [],
            "secondary" : [],
            "tertiary" : [],
        };
    }

    show() {
        switch(this.map.l_map.getZoom())
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:

                break;
        }
    }
}

class Map {
    constructor() {
        this.l_map = L.map('map').setView([0, 0], 0);
        this.l_renderer = L.canvas({ padding: 0.5 });
        this.l_popup = L.popup();

        this.routeLayer = L.layerGroup([]);
        this.graphLayer = L.layerGroup([]);

        this.showNetwork = false;
        this.graphData = [];

        this.style = {
            'nodeColor': 'rgba(255, 255, 0, 0.25)',
            'edgeColor': 'rgba(255, 50, 0, 0.25)',
            'routeColor': 'rgba(0, 150, 255, 0.75)'
        };

        let token = 'pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw';
        L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={token}', {
            maxZoom: 20,
            attribution: '',
            id: 'mapbox.streets',
            token: token
        }).addTo(this.l_map);
    }

    setView(lat, lon) {
        this.l_map.setView([lat, lon], this.l_map.getZoom())
    }

    setGraph(graph) {
        this.graphData = graph;
        this.createGraph();
    }

    createGraph() {
        for (let index = 0; index < this.graphData.length; ++index) {
            for (let edge = 0; edge < this.graphData[index].length; ++edge) {

                // if (graph[index].length >= 1) {
                //     L.circle(graph[index][0], {
                //         radius: 1,
                //         color: this.style['nodeColor'],
                //         interactive: false
                //     }).addTo(graphLayer);
                // }

                if (this.graphData[index].length === 2) {
                    // L.circle(graph[index][1], {
                    //     radius: 1,
                    //     color: this.style['nodeColor'],
                    // }).addTo(graphLayer);

                    L.polyline(this.graphData[index], {
                        renderer: this.l_renderer,
                        color: this.style['edgeColor'],
                        smoothFactor: 500,
                        interactive: false
                    }).addTo(this.graphLayer);
                }
            }
        }
    }

    showGraph(show) {
        this.showNetwork = show;

        if (!this.showNetwork) {
            this.l_map.removeLayer(this.graphLayer);
        } else {
            this.graphLayer.addTo(this.l_map);
        }
    }

    showRoute(lines) {
        this.routeLayer.clearLayers();

        this.routeLayer.addLayer(L.geoJSON({
            type: "LineString",
            coordinates: lines
        }, {
            style: {
                color: this.style['routeColor'],
                weight: 4
            }
        })).addTo(this.l_map);
    }
}

document.addEventListener("DOMContentLoaded", function () {

    new QWebChannel(qt.webChannelTransport, function (channel) {
        window.map = new Map();

        window.ui_graph = new UIGraph(channel.objects.UIGraph, map);
        window.ui_map = new UIMap(channel.objects.UIMap, map);

        window.ui_map.onLoad();
    });
});
