package com.example.hw2_10

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.FlowPreview
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.debounce
import kotlinx.coroutines.flow.distinctUntilChanged
import kotlinx.coroutines.flow.filter
import kotlinx.coroutines.flow.flowOn
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.flow.stateIn
import timber.log.Timber
import kotlin.time.Duration.Companion.milliseconds

class SearchViewModel : ViewModel() {

    private val searchRepository = SearchRepository()

    private val searchQueryFlow = MutableStateFlow("")
    val isLoading = MutableStateFlow(false);


    fun onQueryChanged(query: String) {
        searchQueryFlow.value = query
    }

    @OptIn(FlowPreview::class)
    val searchResults = searchQueryFlow
        .debounce(400.milliseconds)
        .filter { query -> query.trim().length >= 3 }
        .distinctUntilChanged()
        .onEach { isLoading.value = true }
        .map { query -> searchRepository.search(query) }
        .onEach { isLoading.value = false }
        .flowOn(Dispatchers.IO)
        .catch { e -> Timber.e("Search failed: $e");emit(emptyList()) }
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), emptyList())
}