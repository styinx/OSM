var colors = {
    '0': 'rgba(0, 150, 255, 0.75)',
    '1': 'rgba(255, 0, 255, 0.75)',
    '2': 'rgba(255, 255, 0, 0.75)',
    '3': 'rgba(0, 255, 255, 0.75)',
    '4': 'rgba(150, 200, 0, 0.75)',
    '5': 'rgba(255, 150, 255, 0.75)',
    '6': 'rgba(255, 255, 255, 0.75)',
    '7': 'rgba(150, 100, 255, 0.75)',
    '8': 'rgba(50, 150, 50, 0.75)'
};

var style = {
    'nodeColor': 'rgba(255, 255, 0, 0.25)',
    'edgeColor': 'rgba(255, 50, 0, 0.25)',
    'routeColor': 'rgba(0, 150, 255, 0.75)'
};

var icon_blue = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QAAAAAAAD5Q7t/AAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5AIYDjsaZSLkbAAABORJREFUeNrVm22IVkUUx3/PWkipEGutbVprG6bmEOp+iLJXCgqKwJ3tRagkMsEPQmKmuBVFsmpQROGXXin7ENawG6vVRhJumvW0UMFU7pahsqVpq73slqS79mFGBGHhOXNn7nP9f3yeOzPn/O6ZuWfO3FsiD2lbC9wAzAOuABqBOmCcv2IIOAjsBn4AtgPbMOpIatNKCZ0+B7gLeAC4CagR9jAMfAq8BbyHUf+eGQC0HQcsBZb5uxxDvwHPAxswaqi4ALRtBl4ALk4UV3uBRzCqo1gAXLi/CCwiH20ElsSIhlIE5xuAD4GZ5CsL3I5R+6oHQNtZQBcwmeqoH7gVo77PH4C2jf5xVU919SswD6P25AdA2/OAMjCNYqgXuAqj/pQ2rAkc8LUCOQ8wHXg1pGFNwN1/CGimeGpB24Vpp4C2E324Tcxg6AngG+BHYL//rd5H1OyMC/NBYIYkhT5LOMDjGZw/AKz3aW3/KICn+PR5JTApYIw6YDWwIn4EaHsBsAc4V2jUCLAOaKs4cdF2vIf9WEBEDAJTMWog9hqwOMD5IaAFo1pFWZtRgxi1ykfDP8Ixx3tboy+C9wXc+QUY1R48o40ygPY7Q4nujwtA29nADKERqzGqM/PabtRHwFPCVjPR9sqYEXCL0IA+v32NpfX+qSHRzTEBXCcc/EmMOhbNfdeXNAqujwlACVfh9xMkOu1+Ua1Us+IA0HYs0CAYuAujjkZ335XEPha0uBRtz44RAbXAGOE+PWUNQJLk1cYAMEFo5P6EAKR9T4gBQJqJHU0IQFoZHhMDwIBw0JQFkouE1/8eA8ARn9VVqoaEACR9jwB/ZAdg1LBw7t2WxHVtS8K+f/G2R8kDegQDT0XbuQkQNAGXCK6vyOZKAXwlNLY1AYAnhNeXYwL4XDj4fLS9NmL43wjcKWy1MyaA7cBhweAlYJOv8GR1vh54W9hqANgRD4DbjHwQ8DjsQNu6DM5PAjYjP3jpxKjjsQsiIYWNJqCMtnMCnG/y8zhkQa3YVgmAzbiqa8izu4y2L6Pt5Aocn4K2rwBfClf9kzqAO6useK5K7so6XMU2VMN+bm4BduHO/QEuxB1u3AFcI9x8na42jGpNBaDRV2ZqKKZOANMwaneKKQBG/Qx0Uly1S5wn8E62FRjAWmkDOQCjysAnBXS+C6N60gNweqaAAIJsCgNgVLd/LBZFHRi1Iz8ATiuA4wVwfhh3jki+AIzaBbxZAACvY9R3+QNwWgkcqqLzA1m33tkAuCPoVVUEsByjDlUPgNMbuHd689ZnuPeIMynWm6LTgW+BsTk5/x8wJ8v7gTEjAIzqBZ7L8e4/G8P5eACc1uDe90+tn2Km4/EAuMPLhcjf5pBoBFgU89uBuNtal42tTQhgDUZti9lhin3908AXCfrt8dMsqtJ8MqPtZcDXyE+WR9MQMBej+mKbmqay44oSyyP2uDSF8+ki4FQkvAu0ZOxlE0bdk8rE1LW9B3GfwYWqD3g4pYFpARg1CMwH/g6c980Y9deZC+BUlrg4oOWSLNvc4gBwEN4BNghavIRRG/MwLc/6/jJgawXXdQOP5mVUiTzlviHeCVw+yhW9wNV5fDNcHQAOQiPu3O/80/457J3vy9Oc/I+43OmS9nv6kzoG3J2389UB4CB0AwtwHz72A/di1NZqmPI/FK4/MlP45KgAAAAASUVORK5CYII=";
var icon_red = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QAAAAAAAD5Q7t/AAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5AIYDjoss4NAtAAABNVJREFUeNrd22molkUUB/DfvRphKYSmZVmaYmqGpA5U2kpBQRG4VASVRCb4QUhsQyuCwiUoovBLKy0fwgoNbTGK0CzJHqho1RZaLM262qIlufXhGUEE4Z3nnee9r/3hfrnvMzPn/OfMzJlzznRoAQr64nxMxGkYigE4On6yA1vwDb7AGqwKbKtbto4ale6FK3E9LkRnYhd78DaewYuBfw4LAopyVmdhdpzlHPgFD2JxKK2lPQkomIyHcFJNhvU9bg4saysCork/jOlag2cxM4c1dGRQfjBewyitxae4LPBDtxFQMBorcaLuwUZcEvi85QQU5VG2BgN1L37GxMB3LSOg4Bisw3DtgfU4M/BHasPOigM+0UbKwwg8XqVhZ4XZv1F53LUbphZMq3UJFPSL5tavCUH34SN8hU3xfwOjRZ3R5Ma8BSNTXOieiQPc2YTym7EourUbD0HwoOg+347jKowxAHNxa3YLKOiv3GmPShRqLxZifqOOS0HvSPZtFSxiO4YEunLvATMqKL8DUwPzUry2wPbAHdEa/k4cs3eUNfsmeG2Fmb8msLTqgg68hCnxZpiC67ISUJSb08hEIeYGlje7tQdexz2JzUYVjMlpARcnCrAhXl9zYVE8NVJwUU4Czk0c/O7Arlzax75SreC8nAScnrgLv1yDo7NU2vV3dBYCCo5UXnkbxcrAztzax5DYGwlNTik4IocF9EWPxHt6nTGAFCevbw4C+iQKualGAlL77pODgFRPbGeNBKRGhnvkIKArcdA6AyQnJH7/Ww4CtkWvrlEMrpGAlL734vemCQilG5qy9i6tQ/OiXIopff8UGnChOxsfv2EMKRhXAwfjcXIaZ/kcoQ8ShZ1XAwF3JX6/LicB7yUOPqngnIzmfwGuSGy2NicBa7A1YfAOLIkRnmaVH4jnEpt14d1sBMTLyKsVjsNlRRMJ0qIMi62QnnhZHtidOyBSJbAxHusKxlZQfnxcx1U21IZlTSFghTLqWuXsXlfwaNHATBYMKngM7yfu+vuxWZmrbHitpszKQmXEtir2xLX5Cr5U5v3heGVy43JMSLx8HYz5IeEUSiVgaIzMdGpP7MPwUJbaZF8CAt/KEOerEUtTlFdxJue3MQELUhskExDKnfnNNlR+ZUhz2StbANzbhgRUkqkSAYHV8VhsFywLDXp+uSyAMgG5uw2U36PMI2opAaE8x59uAwKeDHxWtXGzRVL9lKWt/btJ+S6MCvzacguIVtClzOJ2F+Y0o3zTBEQ8pazpbTXeUdYRN4VclaIj8LEyi9QK/IuxzdQH5rQAoawbeqCFs39/DuWzWUC0gl74BMNqVv5rjMlVPp/tVhcFmia9miMFezE959uBrNfa6I0tqJGA+wKrcnZYx4OJnnGHPit/1ybkLLyohYAo6TB8KD2zfCjswLhQlt5kRS2RnRiUmJOxy1l1KF+bBRxgCS9gapPdLAlcXZeMdcf2boh3harYgJvqFLBWAkJZMDUJf1Vc95MDfx62BBzgJc6o0HRmM9fctiEgkvA8Fic0eSSUL8P8LwiImI23GvhuNW5plVAdLSRg/xvitTj1EJ+sx9mteDPcLQREEoYq837HHvTT1qj8hlbK0/IUV8wuTYl3+v3YhatarXy3omBywY/xr9seYf0HXNIMyfp4RR8AAAAASUVORK5CYII=";

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
        this.map.routeLayer.clearLayers();
        this.map.l_map.removeLayer(this.map.l_popup);

        latlon = latlon.split(",");
        this.map.l_start.setLatLng(latlon).addTo(this.map.l_map);
    }

    setStop(latlon) {
        this.cpp_ui_map.setStop(latlon);
        this.map.routeLayer.clearLayers();
        this.map.l_map.removeLayer(this.map.l_popup);

        latlon = latlon.split(",");
        this.map.l_stop.setLatLng(latlon).addTo(this.map.l_map);
    }

    // C++ -> JS

    setView(lat, lon, zoom) {
        this.map.setView(lat, lon, zoom);
    }

    setGraph(graph) {
        this.map.setGraph(graph);
    }

    showGraph(bool) {
        this.map.showGraph(bool);
    }

    showRoute(route, color) {
        this.map.showRoute(route, color);
    }
}

class UIGraph {
    constructor(cpp_ui_graph, map) {
        this.cpp_ui_graph = cpp_ui_graph;
        this.map = map;
        this.l_renderer = L.canvas({padding: 0.5});

        this.graphs = {"motorway": []};
        this.layers = {"motorway": L.layerGroup([])};
    }

    computeGraph(tpye) {

    }

    show() {
        let zoom = this.map.l_map.getZoom();

        console.log(JSON.stringify(this.cpp_ui_graph.motorway));
        this.graphs["motorway"] = JSON.parse(this.cpp_ui_graph.motorway);

        L.polyline(this.graphs["motorway"], {
            renderer: this.l_renderer,
            color: style['edgeColor'],
            interactive: false
        }).addTo(this.map.l_map);

        this.motorway.addTo(this.map.l_map);

        if (zoom > 15) {

        }
    }
}

class Map {
    constructor() {
        this.l_map = L.map('map').setView([0, 0], 10);

        let blue_icon = L.icon({
            iconUrl: icon_blue,
            opacity: 0.5,
            iconSize: [32, 32],
            iconAnchor: [16, 32]
        });

        let red_icon = L.icon({
            iconUrl: icon_red,
            opacity: 0.5,
            iconSize: [32, 32],
            iconAnchor: [16, 32]
        });

        this.l_popup = L.popup();
        this.l_start = L.marker([0, 0], {icon: blue_icon}).bindPopup("Start");
        this.l_stop = L.marker([0, 0], {icon: red_icon}).bindPopup("Stop");

        this.routeLayer = L.layerGroup([]);
        this.graphLayer = L.layerGroup([]);

        this.showNetwork = false;

        let token = 'pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw';
        L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={token}', {
            maxZoom: 20,
            attribution: '',
            id: 'mapbox.streets',
            token: token
        }).addTo(this.l_map);
    }

    setView(lat, lon, zoom = -1) {
        let _zoom = zoom === -1 ? this.l_map.getZoom() : zoom;

        this.l_map.setView([lat, lon], _zoom);
    }

    showGraph(show) {
        this.showNetwork = show;

        if (!this.showNetwork) {
            this.l_map.removeLayer(this.graphLayer);
        } else {
            this.graphLayer.addTo(this.l_map);
        }
    }

    showRoute(lines, color) {
        this.routeLayer.clearLayers();

        this.routeLayer.addLayer(L.geoJSON({
            type: "LineString",
            coordinates: lines
        }, {
            style: {
                color: color ? colors[color] : style['routeColor'],
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
