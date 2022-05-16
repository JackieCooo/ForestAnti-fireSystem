import {createStore} from "vuex";

const store = createStore({
    state: {
        user: {
            id: null,
            name: null,
        },
    },
    mutations: {
        login(state, user) {
            state.user.id = user.id
            state.user.name = user.name
        },
        logout(state) {
            state.user.id = null
            state.user.name = null
        }
    },
})

export default store